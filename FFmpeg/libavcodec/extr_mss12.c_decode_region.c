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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  PixContext ;
typedef  int /*<<< orphan*/  ArithCoder ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB24 (int*,int /*<<< orphan*/  const) ; 
 int decode_pixel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_pixel_in_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int,int,int) ; 

__attribute__((used)) static int decode_region(ArithCoder *acoder, uint8_t *dst, uint8_t *rgb_pic,
                         int x, int y, int width, int height, ptrdiff_t stride,
                         ptrdiff_t rgb_stride, PixContext *pctx,
                         const uint32_t *pal)
{
    int i, j, p;
    uint8_t *rgb_dst = rgb_pic + x * 3 + y * rgb_stride;

    dst += x + y * stride;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            if (!i && !j)
                p = decode_pixel(acoder, pctx, NULL, 0, 0);
            else
                p = decode_pixel_in_context(acoder, pctx, dst + i, stride,
                                            i, j, width - i - 1);
            if (p < 0)
                return p;
            dst[i] = p;

            if (rgb_pic)
                AV_WB24(rgb_dst + i * 3, pal[p]);
        }
        dst     += stride;
        rgb_dst += rgb_stride;
    }

    return 0;
}