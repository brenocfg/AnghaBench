#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n; double* z; int* mean; int count; int* covariance; } ;
typedef  TYPE_1__ PCA ;

/* Variables and functions */
 int const FFMAX (int,int) ; 
 int const FFMIN (int,int) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 
 double sqrt (int) ; 

int ff_pca(PCA *pca, double *eigenvector, double *eigenvalue){
    int i, j, pass;
    int k=0;
    const int n= pca->n;
    double *z = pca->z;

    memset(eigenvector, 0, sizeof(double)*n*n);

    for(j=0; j<n; j++){
        pca->mean[j] /= pca->count;
        eigenvector[j + j*n] = 1.0;
        for(i=0; i<=j; i++){
            pca->covariance[j + i*n] /= pca->count;
            pca->covariance[j + i*n] -= pca->mean[i] * pca->mean[j];
            pca->covariance[i + j*n] = pca->covariance[j + i*n];
        }
        eigenvalue[j]= pca->covariance[j + j*n];
        z[j]= 0;
    }

    for(pass=0; pass < 50; pass++){
        double sum=0;

        for(i=0; i<n; i++)
            for(j=i+1; j<n; j++)
                sum += fabs(pca->covariance[j + i*n]);

        if(sum == 0){
            for(i=0; i<n; i++){
                double maxvalue= -1;
                for(j=i; j<n; j++){
                    if(eigenvalue[j] > maxvalue){
                        maxvalue= eigenvalue[j];
                        k= j;
                    }
                }
                eigenvalue[k]= eigenvalue[i];
                eigenvalue[i]= maxvalue;
                for(j=0; j<n; j++){
                    double tmp= eigenvector[k + j*n];
                    eigenvector[k + j*n]= eigenvector[i + j*n];
                    eigenvector[i + j*n]= tmp;
                }
            }
            return pass;
        }

        for(i=0; i<n; i++){
            for(j=i+1; j<n; j++){
                double covar= pca->covariance[j + i*n];
                double t,c,s,tau,theta, h;

                if(pass < 3 && fabs(covar) < sum / (5*n*n)) //FIXME why pass < 3
                    continue;
                if(fabs(covar) == 0.0) //FIXME should not be needed
                    continue;
                if(pass >=3 && fabs((eigenvalue[j]+z[j])/covar) > (1LL<<32) && fabs((eigenvalue[i]+z[i])/covar) > (1LL<<32)){
                    pca->covariance[j + i*n]=0.0;
                    continue;
                }

                h= (eigenvalue[j]+z[j]) - (eigenvalue[i]+z[i]);
                theta=0.5*h/covar;
                t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                if(theta < 0.0) t = -t;

                c=1.0/sqrt(1+t*t);
                s=t*c;
                tau=s/(1.0+c);
                z[i] -= t*covar;
                z[j] += t*covar;

#define ROTATE(a,i,j,k,l) {\
    double g=a[j + i*n];\
    double h=a[l + k*n];\
    a[j + i*n]=g-s*(h+g*tau);\
    a[l + k*n]=h+s*(g-h*tau); }
                for(k=0; k<n; k++) {
                    if(k!=i && k!=j){
                        ROTATE(pca->covariance,FFMIN(k,i),FFMAX(k,i),FFMIN(k,j),FFMAX(k,j))
                    }
                    ROTATE(eigenvector,k,i,k,j)
                }
                pca->covariance[j + i*n]=0.0;
            }
        }
        for (i=0; i<n; i++) {
            eigenvalue[i] += z[i];
            z[i]=0.0;
        }
    }

    return -1;
}