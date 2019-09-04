#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int height; int width; TYPE_3__* state; } ;
typedef  TYPE_2__ zbar_window_t ;
struct TYPE_9__ {int logo_scale; TYPE_1__* logo_z; scalar_t__ logo_zbars; TYPE_4__* logo_bars; } ;
typedef  TYPE_3__ window_state_t ;
struct TYPE_10__ {int x; int y; int width; int height; } ;
typedef  TYPE_4__ XRectangle ;
struct TYPE_7__ {int x; int y; } ;

/* Variables and functions */
 scalar_t__ XCreateRegion () ; 
 int /*<<< orphan*/  XDestroyRegion (scalar_t__) ; 
 int /*<<< orphan*/  XUnionRectWithRegion (TYPE_4__*,scalar_t__,scalar_t__) ; 

int _zbar_window_resize (zbar_window_t *w)
{
    window_state_t *x = w->state;
    if(!x)
        return(0);

    int lbw;
    if(w->height * 8 / 10 <= w->width)
        lbw = w->height / 36;
    else
        lbw = w->width * 5 / 144;
    if(lbw < 1)
        lbw = 1;
    x->logo_scale = lbw;
    if(x->logo_zbars)
        XDestroyRegion(x->logo_zbars);
    x->logo_zbars = XCreateRegion();

    int x0 = w->width / 2;
    int y0 = w->height / 2;
    int by0 = y0 - 54 * lbw / 5;
    int bh = 108 * lbw / 5;

    static const int bx[5] = { -6, -3, -1,  2,  5 };
    static const int bw[5] = {  1,  1,  2,  2,  1 };

    int i;
    for(i = 0; i < 5; i++) {
        XRectangle *bar = &x->logo_bars[i];
        bar->x = x0 + lbw * bx[i];
        bar->y = by0;
        bar->width = lbw * bw[i];
        bar->height = bh;
        XUnionRectWithRegion(bar, x->logo_zbars, x->logo_zbars);
    }

    static const int zx[4] = { -7,  7, -7,  7 };
    static const int zy[4] = { -8, -8,  8,  8 };

    for(i = 0; i < 4; i++) {
        x->logo_z[i].x = x0 + lbw * zx[i];
        x->logo_z[i].y = y0 + lbw * zy[i];
    }
    return(0);
}