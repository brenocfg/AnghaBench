#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_7__ {scalar_t__ exposed; } ;
typedef  TYPE_2__ window_state_t ;
struct TYPE_8__ {int x; int y; int width; int height; } ;
typedef  TYPE_3__ XRectangle ;

/* Variables and functions */
 scalar_t__ XCreateRegion () ; 
 int /*<<< orphan*/  XUnionRectWithRegion (TYPE_3__*,scalar_t__,scalar_t__) ; 

int _zbar_window_expose (zbar_window_t *w,
                         int x,
                         int y,
                         int width,
                         int height)
{
    window_state_t *xs = w->state;
    if(!xs->exposed)
        xs->exposed = XCreateRegion();
    XRectangle r;
    r.x = x;
    r.y = y;
    r.width = width;
    r.height = height;
    XUnionRectWithRegion(&r, xs->exposed, xs->exposed);
    return(0);
}