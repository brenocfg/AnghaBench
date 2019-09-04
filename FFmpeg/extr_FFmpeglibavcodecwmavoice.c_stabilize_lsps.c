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

/* Variables and functions */
 double FFMAX (double,double) ; 
 double FFMIN (double,double) ; 
 double M_PI ; 

__attribute__((used)) static void stabilize_lsps(double *lsps, int num)
{
    int n, m, l;

    /* set minimum value for first, maximum value for last and minimum
     * spacing between LSF values.
     * Very similar to ff_set_min_dist_lsf(), but in double. */
    lsps[0]       = FFMAX(lsps[0],       0.0015 * M_PI);
    for (n = 1; n < num; n++)
        lsps[n]   = FFMAX(lsps[n],       lsps[n - 1] + 0.0125 * M_PI);
    lsps[num - 1] = FFMIN(lsps[num - 1], 0.9985 * M_PI);

    /* reorder (looks like one-time / non-recursed bubblesort).
     * Very similar to ff_sort_nearly_sorted_floats(), but in double. */
    for (n = 1; n < num; n++) {
        if (lsps[n] < lsps[n - 1]) {
            for (m = 1; m < num; m++) {
                double tmp = lsps[m];
                for (l = m - 1; l >= 0; l--) {
                    if (lsps[l] <= tmp) break;
                    lsps[l + 1] = lsps[l];
                }
                lsps[l + 1] = tmp;
            }
            break;
        }
    }
}