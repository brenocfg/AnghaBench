#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ mvX; scalar_t__ mvY; int pal_stride; int rgb_stride; int /*<<< orphan*/ * rgb_pic; int /*<<< orphan*/ * pal_pic; int /*<<< orphan*/ * last_rgb_pic; int /*<<< orphan*/ * last_pal_pic; TYPE_1__* avctx; } ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_2__ MSS12Context ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int motion_compensation(MSS12Context const *c,
                               int x, int y, int width, int height)
{
    if (x + c->mvX < 0 || x + c->mvX + width  > c->avctx->width  ||
        y + c->mvY < 0 || y + c->mvY + height > c->avctx->height ||
        !c->rgb_pic)
        return -1;
    else {
        uint8_t *dst     = c->pal_pic + x     + y * c->pal_stride;
        uint8_t *rgb_dst = c->rgb_pic + x * 3 + y * c->rgb_stride;
        uint8_t *src;
        uint8_t *rgb_src;
        int j;
        x += c->mvX;
        y += c->mvY;
        if (c->last_rgb_pic) {
            src     = c->last_pal_pic + x +     y * c->pal_stride;
            rgb_src = c->last_rgb_pic + x * 3 + y * c->rgb_stride;
        } else {
            src     = c->pal_pic + x     + y * c->pal_stride;
            rgb_src = c->rgb_pic + x * 3 + y * c->rgb_stride;
        }
        for (j = 0; j < height; j++) {
            memmove(dst, src, width);
            memmove(rgb_dst, rgb_src, width * 3);
            dst     += c->pal_stride;
            src     += c->pal_stride;
            rgb_dst += c->rgb_stride;
            rgb_src += c->rgb_stride;
        }
    }
    return 0;
}