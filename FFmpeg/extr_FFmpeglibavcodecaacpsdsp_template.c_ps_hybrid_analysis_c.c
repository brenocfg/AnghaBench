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
typedef  int INTFLOAT ;
typedef  int INT64FLOAT ;

/* Variables and functions */

__attribute__((used)) static void ps_hybrid_analysis_c(INTFLOAT (*out)[2], INTFLOAT (*in)[2],
                                 const INTFLOAT (*filter)[8][2],
                                 ptrdiff_t stride, int n)
{
    int i, j;

    for (i = 0; i < n; i++) {
        INT64FLOAT sum_re = (INT64FLOAT)filter[i][6][0] * in[6][0];
        INT64FLOAT sum_im = (INT64FLOAT)filter[i][6][0] * in[6][1];

        for (j = 0; j < 6; j++) {
            INTFLOAT in0_re = in[j][0];
            INTFLOAT in0_im = in[j][1];
            INTFLOAT in1_re = in[12-j][0];
            INTFLOAT in1_im = in[12-j][1];
            sum_re += (INT64FLOAT)filter[i][j][0] * (in0_re + in1_re) -
                      (INT64FLOAT)filter[i][j][1] * (in0_im - in1_im);
            sum_im += (INT64FLOAT)filter[i][j][0] * (in0_im + in1_im) +
                      (INT64FLOAT)filter[i][j][1] * (in0_re - in1_re);
        }
#if USE_FIXED
        out[i * stride][0] = (int)((sum_re + 0x40000000) >> 31);
        out[i * stride][1] = (int)((sum_im + 0x40000000) >> 31);
#else
        out[i * stride][0] = sum_re;
        out[i * stride][1] = sum_im;
#endif /* USE_FIXED */
    }
}