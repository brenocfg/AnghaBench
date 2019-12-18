#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
struct TYPE_5__ {int count; double* covariance; scalar_t__* mean; } ;
typedef  TYPE_1__ PCA ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int LEN ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_lfg_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ fabs (double) ; 
 int /*<<< orphan*/  ff_pca (TYPE_1__*,double*,double*) ; 
 int /*<<< orphan*/  ff_pca_add (TYPE_1__*,double*) ; 
 TYPE_1__* ff_pca_init (int) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(void){
    PCA *pca;
    int i, j, k;
#define LEN 8
    double eigenvector[LEN*LEN];
    double eigenvalue[LEN];
    AVLFG prng;

    av_lfg_init(&prng, 1);

    pca= ff_pca_init(LEN);

    for(i=0; i<9000000; i++){
        double v[2*LEN+100];
        double sum=0;
        int pos = av_lfg_get(&prng) % LEN;
        int v2  = av_lfg_get(&prng) % 101 - 50;
        v[0]    = av_lfg_get(&prng) % 101 - 50;
        for(j=1; j<8; j++){
            if(j<=pos) v[j]= v[0];
            else       v[j]= v2;
            sum += v[j];
        }
/*        for(j=0; j<LEN; j++){
            v[j] -= v[pos];
        }*/
//        sum += av_lfg_get(&prng) % 10;
/*        for(j=0; j<LEN; j++){
            v[j] -= sum/LEN;
        }*/
//        lbt1(v+100,v+100,LEN);
        ff_pca_add(pca, v);
    }


    ff_pca(pca, eigenvector, eigenvalue);
    for(i=0; i<LEN; i++){
        pca->count= 1;
        pca->mean[i]= 0;

//        (0.5^|x|)^2 = 0.5^2|x| = 0.25^|x|


//        pca.covariance[i + i*LEN]= pow(0.5, fabs
        for(j=i; j<LEN; j++){
            printf("%f ", pca->covariance[i + j*LEN]);
        }
        printf("\n");
    }

    for(i=0; i<LEN; i++){
        double v[LEN];
        double error=0;
        memset(v, 0, sizeof(v));
        for(j=0; j<LEN; j++){
            for(k=0; k<LEN; k++){
                v[j] += pca->covariance[FFMIN(k,j) + FFMAX(k,j)*LEN] * eigenvector[i + k*LEN];
            }
            v[j] /= eigenvalue[i];
            error += fabs(v[j] - eigenvector[i + j*LEN]);
        }
        printf("%f ", error);
    }
    printf("\n");

    for(i=0; i<LEN; i++){
        for(j=0; j<LEN; j++){
            printf("%9.6f ", eigenvector[i + j*LEN]);
        }
        printf("  %9.1f %f\n", eigenvalue[i], eigenvalue[i]/eigenvalue[0]);
    }

    return 0;
}