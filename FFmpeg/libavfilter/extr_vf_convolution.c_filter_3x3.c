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
typedef  int uint8_t ;

/* Variables and functions */
 int av_clip_uint8 (int) ; 

__attribute__((used)) static void filter_3x3(uint8_t *dst, int width,
                       float rdiv, float bias, const int *const matrix,
                       const uint8_t *c[], int peak, int radius,
                       int dstride, int stride)
{
    const uint8_t *c0 = c[0], *c1 = c[1], *c2 = c[2];
    const uint8_t *c3 = c[3], *c4 = c[4], *c5 = c[5];
    const uint8_t *c6 = c[6], *c7 = c[7], *c8 = c[8];
    int x;

    for (x = 0; x < width; x++) {
        int sum = c0[x] * matrix[0] + c1[x] * matrix[1] + c2[x] * matrix[2] +
                  c3[x] * matrix[3] + c4[x] * matrix[4] + c5[x] * matrix[5] +
                  c6[x] * matrix[6] + c7[x] * matrix[7] + c8[x] * matrix[8];
        sum = (int)(sum * rdiv + bias + 0.5f);
        dst[x] = av_clip_uint8(sum);
    }
}