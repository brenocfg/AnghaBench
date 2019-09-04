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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (scalar_t__) ; 

__attribute__((used)) static void put_signed_rect_clamped_8bit_c(uint8_t *dst, int dst_stride, const uint8_t *_src, int src_stride, int width, int height)
{
    int x, y;
    int16_t *src = (int16_t *)_src;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x+=4) {
            dst[x  ] = av_clip_uint8(src[x  ] + 128);
            dst[x+1] = av_clip_uint8(src[x+1] + 128);
            dst[x+2] = av_clip_uint8(src[x+2] + 128);
            dst[x+3] = av_clip_uint8(src[x+3] + 128);
        }
        dst += dst_stride;
        src += src_stride >> 1;
    }
}