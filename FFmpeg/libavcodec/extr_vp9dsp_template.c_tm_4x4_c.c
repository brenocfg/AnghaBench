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

__attribute__((used)) static void tm_4x4_c(uint8_t *_dst, ptrdiff_t stride,
                     const uint8_t *_left, const uint8_t *_top)
{
    pixel *dst = (pixel *) _dst;
    const pixel *left = (const pixel *) _left;
    const pixel *top = (const pixel *) _top;
    int y, tl = top[-1];

    stride /= sizeof(pixel);
    for (y = 0; y < 4; y++) {
        int l_m_tl = left[3 - y] - tl;

        dst[0] = av_clip_pixel(top[0] + l_m_tl);
        dst[1] = av_clip_pixel(top[1] + l_m_tl);
        dst[2] = av_clip_pixel(top[2] + l_m_tl);
        dst[3] = av_clip_pixel(top[3] + l_m_tl);
        dst += stride;
    }
}