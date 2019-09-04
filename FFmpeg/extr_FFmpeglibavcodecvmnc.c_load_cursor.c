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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int bpp2; int cur_h; int cur_w; int /*<<< orphan*/  bigendian; int /*<<< orphan*/  gb; int /*<<< orphan*/ * curmask; int /*<<< orphan*/ * curbits; } ;
typedef  TYPE_1__ VmncContext ;

/* Variables and functions */
 int vmnc_get_pixel (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_cursor(VmncContext *c)
{
    int i, j, p;
    const int bpp   = c->bpp2;
    uint8_t *dst8   =             c->curbits;
    uint16_t *dst16 = (uint16_t *)c->curbits;
    uint32_t *dst32 = (uint32_t *)c->curbits;

    for (j = 0; j < c->cur_h; j++) {
        for (i = 0; i < c->cur_w; i++) {
            p = vmnc_get_pixel(&c->gb, bpp, c->bigendian);
            if (bpp == 1)
                *dst8++ = p;
            if (bpp == 2)
                *dst16++ = p;
            if (bpp == 4)
                *dst32++ = p;
        }
    }
    dst8  =            c->curmask;
    dst16 = (uint16_t*)c->curmask;
    dst32 = (uint32_t*)c->curmask;
    for (j = 0; j < c->cur_h; j++) {
        for (i = 0; i < c->cur_w; i++) {
            p = vmnc_get_pixel(&c->gb, bpp, c->bigendian);
            if (bpp == 1)
                *dst8++ = p;
            if (bpp == 2)
                *dst16++ = p;
            if (bpp == 4)
                *dst32++ = p;
        }
    }
}