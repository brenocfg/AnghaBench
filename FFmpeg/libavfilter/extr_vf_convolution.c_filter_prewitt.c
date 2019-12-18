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
 int av_clip_uint8 (float) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void filter_prewitt(uint8_t *dst, int width,
                           float scale, float delta, const int *const matrix,
                           const uint8_t *c[], int peak, int radius,
                           int dstride, int stride)
{
    const uint8_t *c0 = c[0], *c1 = c[1], *c2 = c[2];
    const uint8_t *c3 = c[3], *c5 = c[5];
    const uint8_t *c6 = c[6], *c7 = c[7], *c8 = c[8];
    int x;

    for (x = 0; x < width; x++) {
        float suma = c0[x] * -1 + c1[x] * -1 + c2[x] * -1 +
                     c6[x] *  1 + c7[x] *  1 + c8[x] *  1;
        float sumb = c0[x] * -1 + c2[x] *  1 + c3[x] * -1 +
                     c5[x] *  1 + c6[x] * -1 + c8[x] *  1;

        dst[x] = av_clip_uint8(sqrtf(suma*suma + sumb*sumb) * scale + delta);
    }
}