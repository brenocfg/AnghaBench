#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int REAL ;

/* Variables and functions */
 int /*<<< orphan*/  daxpy (int,int,int*,int,int*,int) ; 
 int ddot (int,int*,int,int*,int) ; 

void dgesl(REAL a[],int lda,int n,int ipvt[],REAL b[],int job )


/* We would like to declare a[][lda], but c does not allow it.  In this
function, references to a[i][j] are written a[lda*i+j].  */

/*
     dgesl solves the double precision system
     a * x = b  or  trans(a) * x = b
     using the factors computed by dgeco or dgefa.

     on entry

        a       double precision[n][lda]
                the output from dgeco or dgefa.

        lda     integer
                the leading dimension of the array  a .

        n       integer
                the order of the matrix  a .

        ipvt    integer[n]
                the pivot vector from dgeco or dgefa.

        b       double precision[n]
                the right hand side vector.

        job     integer
                = 0         to solve  a*x = b ,
                = nonzero   to solve  trans(a)*x = b  where
                            trans(a)  is the transpose.

    on return

        b       the solution vector  x .

     error condition

        a division by zero will occur if the input factor contains a
        zero on the diagonal.  technically this indicates singularity
        but it is often caused by improper arguments or improper
        setting of lda .  it will not occur if the subroutines are
        called correctly and if dgeco has set rcond .gt. 0.0
        or dgefa has set info .eq. 0 .

     to compute  inverse(a) * c  where  c  is a matrix
     with  p  columns
           dgeco(a,lda,n,ipvt,rcond,z)
           if (!rcond is too small){
                for (j=0,j<p,j++)
                        dgesl(a,lda,n,ipvt,c[j][0],0);
           }

     linpack. this version dated 08/14/78 .
     cleve moler, university of new mexico, argonne national lab.

     functions

     blas daxpy,ddot
*/
{
/*     internal variables       */

        REAL t;
        int k,kb,l,nm1;

        nm1 = n - 1;
        if (job == 0) {

                /* job = 0 , solve  a * x = b
                   first solve  l*y = b         */

                if (nm1 >= 1) {
                        for (k = 0; k < nm1; k++) {
                                l = ipvt[k];
                                t = b[l];
                                if (l != k){ 
                                        b[l] = b[k];
                                        b[k] = t;
                                }       
                                daxpy(n-(k+1),t,&a[lda*k+k+1],1,&b[k+1],1 );
                        }
                } 

                /* now solve  u*x = y */

                for (kb = 0; kb < n; kb++) {
                    k = n - (kb + 1);
                    b[k] = b[k]/a[lda*k+k];
                    t = -b[k];
                    daxpy(k,t,&a[lda*k+0],1,&b[0],1 );
                }
        }
        else { 

                /* job = nonzero, solve  trans(a) * x = b
                   first solve  trans(u)*y = b                  */

                for (k = 0; k < n; k++) {
                        t = ddot(k,&a[lda*k+0],1,&b[0],1);
                        b[k] = (b[k] - t)/a[lda*k+k];
                }

                /* now solve trans(l)*x = y     */

                if (nm1 >= 1) {
                        for (kb = 1; kb < nm1; kb++) {
                                k = n - (kb+1);
                                b[k] = b[k] + ddot(n-(k+1),&a[lda*k+k+1],1,&b[k+1],1);
                                l = ipvt[k];
                                if (l != k) {
                                        t = b[l];
                                        b[l] = b[k];
                                        b[k] = t;
                                }
                        }
                }
        }
        return;
}