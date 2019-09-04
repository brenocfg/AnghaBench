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
typedef  scalar_t__ REAL ;

/* Variables and functions */
 scalar_t__ fabs (double) ; 

int idamax(int n, REAL dx[], int incx)

/*
     finds the index of element having max. absolute value.
     jack dongarra, linpack, 3/11/78.
*/


{
        REAL dmax;
        int i, ix, itemp;

        if( n < 1 ) return(-1);
        if(n ==1 ) return(0);
        if(incx != 1) {

                /* code for increment not equal to 1 */

                ix = 1;
                dmax = fabs((double)dx[0]);
                ix = ix + incx;
                for (i = 1; i < n; i++) {
                        if(fabs((double)dx[ix]) > dmax)  {
                                itemp = i;
                                dmax = fabs((double)dx[ix]);
                        }
                        ix = ix + incx;
                }
        }
        else {

                /* code for increment equal to 1 */

                itemp = 0;
                dmax = fabs((double)dx[0]);
                for (i = 1; i < n; i++) {
                        if(fabs((double)dx[i]) > dmax) {
                                itemp = i;
                                dmax = fabs((double)dx[i]);
                        }
                }
        }
        return (itemp);
}