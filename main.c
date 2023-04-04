#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ETATS 100 // nombre d'états maximale
#define  MAX_ACTIONS 100 // nombre d'actions maximale

// Les variables globale

int nomEtats;  // nombre d'états dans le problème
int nomActions; // nombre d'actions possibles dans chaque état
float alpha; // facteur d'actualisation
float epsilon; // seuil de convergence

float V[MAX_ETATS]; // Le vecteur gain optimal
int strategie[MAX_ETATS]; // les stratégies

// définir les probabilités de transition et les récompenses pour chaque couple état-action
float T[MAX_ETATS][MAX_ACTIONS][MAX_ETATS];
/*
= {
        {{0.3333, 0.6666}, {0.5, 0.5}},
        {{0.25, 0.75}, {0, 1}}
};
 */
float R[MAX_ETATS][MAX_ACTIONS];
/*
= {{1, 0},
 {3, 2}
};
 */


// fonction pour calculer la valeur de chaque état à l'aide de l'équation de Bellman
void valueIteration(float V[nomEtats], int policy[nomEtats])
{
    int i, j, a;
    float maxVal, newVal, newVoldV, temp;
    float oldV[nomEtats];

    do {
        for (i = 0; i < nomEtats; i++) {
            oldV[i] = V[i];
        }

        maxVal = -INFINITY;
        for (i = 0; i < nomEtats; i++) {
            for (a = 0; a < nomActions; a++) {
                newVal = R[i][a];
                for (j = 0; j < nomEtats; j++) {
                    newVal += alpha * T[i][a][j] * V[j];
                }
                if (newVal > maxVal) {
                    maxVal = newVal;
                    policy[i] = a;
                }
            }
            V[i] = maxVal;
            maxVal = -INFINITY;
        }

        newVoldV = -INFINITY;

        for (i = 0; i < nomEtats; i++) {
            temp = V[i] - oldV[i];
            if (temp < 0) temp = -temp;
            if (temp > newVoldV) newVoldV = temp;
        }

    } while (newVoldV > epsilon);
}

int main()
{
    int i, j, k;

    printf("------- Algorithme d'itération de la valeur - critère d’actualisation -------\n");

    printf("Veuillez saisire le nombre des états: ");
    scanf("%d", &nomEtats);

    printf("Veuillez saisire le nombre des actions: ");
    scanf("%d", &nomActions);

    printf("Veuillez saisire le facteur d'actualisation (ALPHA): ");
    scanf("%f", &alpha);

    printf("Veuillez saisire le seuil de convergence (EPSILON): ");
    scanf("%f", &epsilon);

    printf("\n------- les probabilités de transition et les récompenses pour chaque couple état-action -------\n");
    printf("les probabilités de transition pour chaque couple état-action : \n");

    for (i = 0; i < nomEtats; ++i) {
        printf("l'état %d\n", i+1);
        for (j = 0; j < nomActions; ++j) {
            for (k = 0; k < nomEtats; ++k) {
                printf("la probabilité de passer de l'état %d à l'état %d avec l'action %d\n", i+1, k+1, j+1);
                printf("P = ");
                scanf("%f", &T[i][j][k]);
            }
        }
    }

    printf("les récompenses pour chaque couple état-action : \n");

    for (i = 0; i < nomEtats ; ++i) {
        for (j = 0; j < nomActions; ++j) {
            printf("la récompense de l'action %d dans l'état %d : \n", j+1, i+1);
            printf("R = ");
            scanf("%f", &R[i][j]);

        }
    }

    // initialiser toutes les valeurs d'état à 0
    for (i = 0; i < nomEtats; i++) {
        V[i] = 0.0;
    }

    // initialiser toutes les stratégies à la première action
    for (i = 0; i < nomEtats; i++) {
        strategie[i] = 0;
    }

    valueIteration(V, strategie);

    printf("\n------- Résultat : la stratégie optimale et le vecteur gain optimal ------- \n");

    printf("La stratégie optimale:\n");
    for (i = 0; i < nomEtats; i++) {
        printf("Etat : %d -- Action : %d\n", i+1, strategie[i]+1);
    }
    printf("\nLe vecteur gain optimal: \n");
    for (i = 0; i < nomEtats; i++) {
        printf("V[%d] = %.2f\n",i+1 ,V[i]);
    }

    return 0;
}
