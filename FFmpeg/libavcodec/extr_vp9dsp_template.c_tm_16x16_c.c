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
typedef  int ptrdiff_t ;
typedef  int pixel ;

/* Variables and functions */
 int av_clip_pixel (int const) ; 

__attribute__((used)) static void tm_16x16_c(uint8_t *_dst, ptrdiff_t stride,
                       const uint8_t *_left, const uint8_t *_top)
{
    pixel *dst = (pixel *) _dst;
    const pixel *left = (const pixel *) _left;
    const pixel *top = (const pixel *) _top;
    int y, tl = top[-1];

    stride /= sizeof(pixel);
    for (y = 0; y < 16; y++) {
        int l_m_tl = left[15 - y] - tl;

        dst[ 0] = av_clip_pixel(top[ 0] + l_m_tl);
        dst[ 1] = av_clip_pixel(top[ 1] + l_m_tl);
        dst[ 2] = av_clip_pixel(top[ 2] + l_m_tl);
        dst[ 3] = av_clip_pixel(top[ 3] + l_m_tl);
        dst[ 4] = av_clip_pixel(top[ 4] + l_m_tl);
        dst[ 5] = av_clip_pixel(top[ 5] + l_m_tl);
        dst[ 6] = av_clip_pixel(top[ 6] + l_m_tl);
        dst[ 7] = av_clip_pixel(top[ 7] + l_m_tl);
        dst[ 8] = av_clip_pixel(top[ 8] + l_m_tl);
        dst[ 9] = av_clip_pixel(top[ 9] + l_m_tl);
        dst[10] = av_clip_pixel(top[10] + l_m_tl);
        dst[11] = av_clip_pixel(top[11] + l_m_tl);
        dst[12] = av_clip_pixel(top[12] + l_m_tl);
        dst[13] = av_clip_pixel(top[13] + l_m_tl);
        dst[14] = av_clip_pixel(top[14] + l_m_tl);
        dst[15] = av_clip_pixel(top[15] + l_m_tl);
        dst += stride;
    }
}