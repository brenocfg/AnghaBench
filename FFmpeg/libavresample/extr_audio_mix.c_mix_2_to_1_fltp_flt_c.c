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

__attribute__((used)) static void mix_2_to_1_fltp_flt_c(float **samples, float **matrix, int len,
                                  int out_ch, int in_ch)
{
    float *src0 = samples[0];
    float *src1 = samples[1];
    float *dst  = src0;
    float m0    = matrix[0][0];
    float m1    = matrix[0][1];

    while (len > 4) {
        *dst++ = *src0++ * m0 + *src1++ * m1;
        *dst++ = *src0++ * m0 + *src1++ * m1;
        *dst++ = *src0++ * m0 + *src1++ * m1;
        *dst++ = *src0++ * m0 + *src1++ * m1;
        len -= 4;
    }
    while (len > 0) {
        *dst++ = *src0++ * m0 + *src1++ * m1;
        len--;
    }
}