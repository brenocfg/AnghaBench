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
typedef  double REAL ;

/* Variables and functions */

void matgen (REAL a[], int lda, int n, REAL b[], REAL *norma)


/* We would like to declare a[][lda], but c does not allow it.  In this
function, references to a[i][j] are written a[lda*i+j].  */

{
        int init, i, j;

        init = 1325;
        *norma = 0.0;
        for (j = 0; j < n; j++) {
                for (i = 0; i < n; i++) {
                        init = 3125*init % 65536;
                        a[lda*j+i] = (init - 32768.0)/16384.0;                        
                        *norma = (a[lda*j+i] > *norma) ? a[lda*j+i] : *norma;
                        
                        /* alternative for some compilers
                        if (fabs(a[lda*j+i]) > *norma) *norma = fabs(a[lda*j+i]);
                        */
                }
        }
        for (i = 0; i < n; i++) {
          b[i] = 0.0;
        }
        for (j = 0; j < n; j++) {
                for (i = 0; i < n; i++) {
                        b[i] = b[i] + a[lda*j+i];
                }
        }
        return;
}