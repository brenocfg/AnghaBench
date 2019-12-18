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
typedef  int /*<<< orphan*/  pixel ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN4PA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIXEL_SPLAT_X4 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void hor_16x16_c(uint8_t *_dst, ptrdiff_t stride,
                        const uint8_t *_left, const uint8_t *top)
{
    pixel *dst = (pixel *) _dst;
    const pixel *left = (const pixel *) _left;
    int y;

    stride /= sizeof(pixel);
    for (y = 0; y < 16; y++) {
        pixel4 p4 = PIXEL_SPLAT_X4(left[15 - y]);

        AV_WN4PA(dst +  0, p4);
        AV_WN4PA(dst +  4, p4);
        AV_WN4PA(dst +  8, p4);
        AV_WN4PA(dst + 12, p4);
        dst += stride;
    }
}