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
typedef  unsigned int uint8_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void mangle_rgb_planes(uint8_t *dst[4], ptrdiff_t dst_stride,
                              uint8_t *const src[4], int planes, const int stride[4],
                              int width, int height)
{
    int i, j;
    int k = 2 * dst_stride;
    const uint8_t *sg = src[0];
    const uint8_t *sb = src[1];
    const uint8_t *sr = src[2];
    const uint8_t *sa = src[3];
    unsigned int g;

    for (j = 0; j < height; j++) {
        if (planes == 3) {
            for (i = 0; i < width; i++) {
                g         = sg[i];
                dst[0][k] = g;
                g        += 0x80;
                dst[1][k] = sb[i] - g;
                dst[2][k] = sr[i] - g;
                k++;
            }
        } else {
            for (i = 0; i < width; i++) {
                g         = sg[i];
                dst[0][k] = g;
                g        += 0x80;
                dst[1][k] = sb[i] - g;
                dst[2][k] = sr[i] - g;
                dst[3][k] = sa[i];
                k++;
            }
            sa += stride[3];
        }
        k += dst_stride - width;
        sg += stride[0];
        sb += stride[1];
        sr += stride[2];
    }
}