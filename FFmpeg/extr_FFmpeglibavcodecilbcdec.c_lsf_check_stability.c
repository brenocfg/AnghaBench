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
typedef  int int16_t ;

/* Variables and functions */
 int av_clip (int,int,int) ; 

__attribute__((used)) static void lsf_check_stability(int16_t *lsf, int dim, int nb_vectors)
{
    for (int n = 0; n < 2; n++) {
        for (int m = 0; m < nb_vectors; m++) {
            for (int k = 0; k < dim - 1; k++) {
                int i = m * dim + k;

                if ((lsf[i + 1] - lsf[i]) < 319) {
                    if (lsf[i + 1] < lsf[i]) {
                        lsf[i + 1] = lsf[i] + 160;
                        lsf[i]     = lsf[i + 1] - 160;
                    } else {
                        lsf[i]     -= 160;
                        lsf[i + 1] += 160;
                    }
                }

                lsf[i] = av_clip(lsf[i], 82, 25723);
            }
        }
    }
}