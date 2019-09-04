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
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void lfe_iir_c(float *output, const float *input,
                      const float iir[5][4], float hist[5][2],
                      ptrdiff_t factor)
{
    float res, tmp;
    int i, j, k;

    for (i = 0; i < 64; i++) {
        res = *input++;

        for (j = 0; j < factor; j++) {
            for (k = 0; k < 5; k++) {
                tmp = hist[k][0] * iir[k][0] + hist[k][1] * iir[k][1] + res;
                res = hist[k][0] * iir[k][2] + hist[k][1] * iir[k][3] + tmp;

                hist[k][0] = hist[k][1];
                hist[k][1] = tmp;
            }

            *output++ = res;
            res = 0;
        }
    }
}