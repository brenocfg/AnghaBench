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

__attribute__((used)) static void mix_2_to_6_fltp_flt_c(float **samples, float **matrix, int len,
                                  int out_ch, int in_ch)
{
    float v0, v1;
    float *dst0 = samples[0];
    float *dst1 = samples[1];
    float *dst2 = samples[2];
    float *dst3 = samples[3];
    float *dst4 = samples[4];
    float *dst5 = samples[5];
    float *src0 = dst0;
    float *src1 = dst1;

    while (len > 0) {
        v0 = *src0++;
        v1 = *src1++;
        *dst0++ = v0 * matrix[0][0] + v1 * matrix[0][1];
        *dst1++ = v0 * matrix[1][0] + v1 * matrix[1][1];
        *dst2++ = v0 * matrix[2][0] + v1 * matrix[2][1];
        *dst3++ = v0 * matrix[3][0] + v1 * matrix[3][1];
        *dst4++ = v0 * matrix[4][0] + v1 * matrix[4][1];
        *dst5++ = v0 * matrix[5][0] + v1 * matrix[5][1];
        len--;
    }
}