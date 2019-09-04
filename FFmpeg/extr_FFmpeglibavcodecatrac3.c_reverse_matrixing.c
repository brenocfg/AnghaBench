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
 float INTERPOLATE (float,float,int) ; 
 int /*<<< orphan*/  av_assert1 (int /*<<< orphan*/ ) ; 
 float* matrix_coeffs ; 

__attribute__((used)) static void reverse_matrixing(float *su1, float *su2, int *prev_code,
                              int *curr_code)
{
    int i, nsample, band;
    float mc1_l, mc1_r, mc2_l, mc2_r;

    for (i = 0, band = 0; band < 4 * 256; band += 256, i++) {
        int s1 = prev_code[i];
        int s2 = curr_code[i];
        nsample = band;

        if (s1 != s2) {
            /* Selector value changed, interpolation needed. */
            mc1_l = matrix_coeffs[s1 * 2    ];
            mc1_r = matrix_coeffs[s1 * 2 + 1];
            mc2_l = matrix_coeffs[s2 * 2    ];
            mc2_r = matrix_coeffs[s2 * 2 + 1];

            /* Interpolation is done over the first eight samples. */
            for (; nsample < band + 8; nsample++) {
                float c1 = su1[nsample];
                float c2 = su2[nsample];
                c2 = c1 * INTERPOLATE(mc1_l, mc2_l, nsample - band) +
                     c2 * INTERPOLATE(mc1_r, mc2_r, nsample - band);
                su1[nsample] = c2;
                su2[nsample] = c1 * 2.0 - c2;
            }
        }

        /* Apply the matrix without interpolation. */
        switch (s2) {
        case 0:     /* M/S decoding */
            for (; nsample < band + 256; nsample++) {
                float c1 = su1[nsample];
                float c2 = su2[nsample];
                su1[nsample] =  c2       * 2.0;
                su2[nsample] = (c1 - c2) * 2.0;
            }
            break;
        case 1:
            for (; nsample < band + 256; nsample++) {
                float c1 = su1[nsample];
                float c2 = su2[nsample];
                su1[nsample] = (c1 + c2) *  2.0;
                su2[nsample] =  c2       * -2.0;
            }
            break;
        case 2:
        case 3:
            for (; nsample < band + 256; nsample++) {
                float c1 = su1[nsample];
                float c2 = su2[nsample];
                su1[nsample] = c1 + c2;
                su2[nsample] = c1 - c2;
            }
            break;
        default:
            av_assert1(0);
        }
    }
}