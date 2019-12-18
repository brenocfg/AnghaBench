#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int cur_w; scalar_t__ width; scalar_t__ cur_x; int cur_h; scalar_t__ height; scalar_t__ cur_y; int bpp2; int* curbits; int* curmask; } ;
typedef  TYPE_1__ VmncContext ;

/* Variables and functions */

__attribute__((used)) static void put_cursor(uint8_t *dst, int stride, VmncContext *c, int dx, int dy)
{
    int i, j;
    int w, h, x, y;
    w = c->cur_w;
    if (c->width < c->cur_x + c->cur_w)
        w = c->width - c->cur_x;
    h = c->cur_h;
    if (c->height < c->cur_y + c->cur_h)
        h = c->height - c->cur_y;
    x = c->cur_x;
    y = c->cur_y;
    if (x < 0) {
        w += x;
        x  = 0;
    }
    if (y < 0) {
        h += y;
        y  = 0;
    }

    if ((w < 1) || (h < 1))
        return;
    dst += x * c->bpp2 + y * stride;

    if (c->bpp2 == 1) {
        uint8_t *cd = c->curbits, *msk = c->curmask;
        for (j = 0; j < h; j++) {
            for (i = 0; i < w; i++)
                dst[i] = (dst[i] & cd[i]) ^ msk[i];
            msk += c->cur_w;
            cd  += c->cur_w;
            dst += stride;
        }
    } else if (c->bpp2 == 2) {
        uint16_t *cd = (uint16_t*)c->curbits, *msk = (uint16_t*)c->curmask;
        uint16_t *dst2;
        for (j = 0; j < h; j++) {
            dst2 = (uint16_t*)dst;
            for (i = 0; i < w; i++)
                dst2[i] = (dst2[i] & cd[i]) ^ msk[i];
            msk += c->cur_w;
            cd  += c->cur_w;
            dst += stride;
        }
    } else if (c->bpp2 == 4) {
        uint32_t *cd = (uint32_t*)c->curbits, *msk = (uint32_t*)c->curmask;
        uint32_t *dst2;
        for (j = 0; j < h; j++) {
            dst2 = (uint32_t*)dst;
            for (i = 0; i < w; i++)
                dst2[i] = (dst2[i] & cd[i]) ^ msk[i];
            msk += c->cur_w;
            cd  += c->cur_w;
            dst += stride;
        }
    }
}