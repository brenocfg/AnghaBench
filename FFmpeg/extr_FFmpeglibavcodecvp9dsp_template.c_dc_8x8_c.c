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
typedef  int /*<<< orphan*/  pixel4 ;
typedef  int pixel ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN4PA (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIXEL_SPLAT_X4 (int const) ; 

__attribute__((used)) static void dc_8x8_c(uint8_t *_dst, ptrdiff_t stride,
                     const uint8_t *_left, const uint8_t *_top)
{
    pixel *dst = (pixel *) _dst;
    const pixel *left = (const pixel *) _left;
    const pixel *top = (const pixel *) _top;
    pixel4 dc = PIXEL_SPLAT_X4
        ((left[0] + left[1] + left[2] + left[3] + left[4] + left[5] +
          left[6] + left[7] + top[0] + top[1] + top[2] + top[3] +
          top[4] + top[5] + top[6] + top[7] + 8) >> 4);
    int y;

    stride /= sizeof(pixel);
    for (y = 0; y < 8; y++) {
        AV_WN4PA(dst + 0, dc);
        AV_WN4PA(dst + 4, dc);
        dst += stride;
    }
}