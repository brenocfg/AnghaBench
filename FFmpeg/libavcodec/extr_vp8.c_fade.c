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
typedef  int ptrdiff_t ;

/* Variables and functions */
 int av_clip_uint8 (int) ; 

__attribute__((used)) static void fade(uint8_t *dst, ptrdiff_t dst_linesize,
                 const uint8_t *src, ptrdiff_t src_linesize,
                 int width, int height,
                 int alpha, int beta)
{
    int i, j;
    for (j = 0; j < height; j++) {
        const uint8_t *src2 = src + j * src_linesize;
        uint8_t *dst2 = dst + j * dst_linesize;
        for (i = 0; i < width; i++) {
            uint8_t y = src2[i];
            dst2[i] = av_clip_uint8(y + ((y * beta) >> 8) + alpha);
        }
    }
}