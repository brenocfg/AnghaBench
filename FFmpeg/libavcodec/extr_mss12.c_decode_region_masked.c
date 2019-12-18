#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_7__ {int* rgb_pic; int rgb_stride; int /*<<< orphan*/ * pal; TYPE_1__* avctx; } ;
struct TYPE_6__ {int err_recognition; } ;
typedef  int /*<<< orphan*/  PixContext ;
typedef  TYPE_2__ MSS12Context ;
typedef  int /*<<< orphan*/  ArithCoder ;

/* Variables and functions */
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_WB24 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_rectangles (TYPE_2__ const*,int,int,int,int) ; 
 int decode_pixel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_pixel_in_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int,int,int) ; 
 scalar_t__ motion_compensation (TYPE_2__ const*,int,int,int,int) ; 

__attribute__((used)) static int decode_region_masked(MSS12Context const *c, ArithCoder *acoder,
                                uint8_t *dst, ptrdiff_t stride, uint8_t *mask,
                                ptrdiff_t mask_stride, int x, int y,
                                int width, int height,
                                PixContext *pctx)
{
    int i, j, p;
    uint8_t *rgb_dst = c->rgb_pic + x * 3 + y * c->rgb_stride;

    dst  += x + y * stride;
    mask += x + y * mask_stride;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            if (c->avctx->err_recognition & AV_EF_EXPLODE &&
                ( c->rgb_pic && mask[i] != 0x01 && mask[i] != 0x02 && mask[i] != 0x04 ||
                 !c->rgb_pic && mask[i] != 0x80 && mask[i] != 0xFF))
                return -1;

            if (mask[i] == 0x02) {
                copy_rectangles(c, x + i, y + j, 1, 1);
            } else if (mask[i] == 0x04) {
                if (motion_compensation(c, x + i, y + j, 1, 1))
                    return -1;
            } else if (mask[i] != 0x80) {
                if (!i && !j)
                    p = decode_pixel(acoder, pctx, NULL, 0, 0);
                else
                    p = decode_pixel_in_context(acoder, pctx, dst + i, stride,
                                                i, j, width - i - 1);
                if (p < 0)
                    return p;
                dst[i] = p;
                if (c->rgb_pic)
                    AV_WB24(rgb_dst + i * 3, c->pal[p]);
            }
        }
        dst     += stride;
        mask    += mask_stride;
        rgb_dst += c->rgb_stride;
    }

    return 0;
}