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

__attribute__((used)) static void mix_6_to_2_fltp_flt_c(float **samples, float **matrix, int len,
                                  int out_ch, int in_ch)
{
    float v0, v1;
    float *src0 = samples[0];
    float *src1 = samples[1];
    float *src2 = samples[2];
    float *src3 = samples[3];
    float *src4 = samples[4];
    float *src5 = samples[5];
    float *dst0 = src0;
    float *dst1 = src1;
    float *m0   = matrix[0];
    float *m1   = matrix[1];

    while (len > 0) {
        v0 = *src0++;
        v1 = *src1++;
        *dst0++ = v0      * m0[0] +
                  v1      * m0[1] +
                  *src2   * m0[2] +
                  *src3   * m0[3] +
                  *src4   * m0[4] +
                  *src5   * m0[5];
        *dst1++ = v0      * m1[0] +
                  v1      * m1[1] +
                  *src2++ * m1[2] +
                  *src3++ * m1[3] +
                  *src4++ * m1[4] +
                  *src5++ * m1[5];
        len--;
    }
}