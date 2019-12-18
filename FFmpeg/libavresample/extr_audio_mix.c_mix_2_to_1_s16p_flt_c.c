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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 void* av_clip_int16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lrintf (float) ; 

__attribute__((used)) static void mix_2_to_1_s16p_flt_c(int16_t **samples, float **matrix, int len,
                                  int out_ch, int in_ch)
{
    int16_t *src0 = samples[0];
    int16_t *src1 = samples[1];
    int16_t *dst  = src0;
    float m0      = matrix[0][0];
    float m1      = matrix[0][1];

    while (len > 4) {
        *dst++ = av_clip_int16(lrintf(*src0++ * m0 + *src1++ * m1));
        *dst++ = av_clip_int16(lrintf(*src0++ * m0 + *src1++ * m1));
        *dst++ = av_clip_int16(lrintf(*src0++ * m0 + *src1++ * m1));
        *dst++ = av_clip_int16(lrintf(*src0++ * m0 + *src1++ * m1));
        len -= 4;
    }
    while (len > 0) {
        *dst++ = av_clip_int16(lrintf(*src0++ * m0 + *src1++ * m1));
        len--;
    }
}