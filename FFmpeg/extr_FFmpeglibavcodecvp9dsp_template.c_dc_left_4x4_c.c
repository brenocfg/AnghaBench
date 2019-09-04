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

__attribute__((used)) static void dc_left_4x4_c(uint8_t *_dst, ptrdiff_t stride,
                          const uint8_t *_left, const uint8_t *top)
{
    pixel *dst = (pixel *) _dst;
    const pixel *left = (const pixel *) _left;
    pixel4 dc = PIXEL_SPLAT_X4((left[0] + left[1] + left[2] + left[3] + 2) >> 2);

    stride /= sizeof(pixel);
    AV_WN4PA(dst + stride * 0, dc);
    AV_WN4PA(dst + stride * 1, dc);
    AV_WN4PA(dst + stride * 2, dc);
    AV_WN4PA(dst + stride * 3, dc);
}