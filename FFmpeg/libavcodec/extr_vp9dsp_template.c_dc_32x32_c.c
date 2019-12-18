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

__attribute__((used)) static void dc_32x32_c(uint8_t *_dst, ptrdiff_t stride,
                       const uint8_t *_left, const uint8_t *_top)
{
    pixel *dst = (pixel *) _dst;
    const pixel *left = (const pixel *) _left;
    const pixel *top = (const pixel *) _top;
    pixel4 dc = PIXEL_SPLAT_X4
        ((left[0] + left[1] + left[2] + left[3] + left[4] + left[5] + left[6] +
          left[7] + left[8] + left[9] + left[10] + left[11] + left[12] +
          left[13] + left[14] + left[15] + left[16] + left[17] + left[18] +
          left[19] + left[20] + left[21] + left[22] + left[23] + left[24] +
          left[25] + left[26] + left[27] + left[28] + left[29] + left[30] +
          left[31] + top[0] + top[1] + top[2] + top[3] + top[4] + top[5] +
          top[6] + top[7] + top[8] + top[9] + top[10] + top[11] + top[12] +
          top[13] + top[14] + top[15] + top[16] + top[17] + top[18] + top[19] +
          top[20] + top[21] + top[22] + top[23] + top[24] + top[25] + top[26] +
          top[27] + top[28] + top[29] + top[30] + top[31] + 32) >> 6);
    int y;

    stride /= sizeof(pixel);
    for (y = 0; y < 32; y++) {
        AV_WN4PA(dst +  0, dc);
        AV_WN4PA(dst +  4, dc);
        AV_WN4PA(dst +  8, dc);
        AV_WN4PA(dst + 12, dc);
        AV_WN4PA(dst + 16, dc);
        AV_WN4PA(dst + 20, dc);
        AV_WN4PA(dst + 24, dc);
        AV_WN4PA(dst + 28, dc);
        dst += stride;
    }
}