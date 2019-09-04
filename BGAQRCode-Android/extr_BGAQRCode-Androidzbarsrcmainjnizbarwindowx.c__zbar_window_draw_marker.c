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
struct TYPE_6__ {int /*<<< orphan*/  xwin; int /*<<< orphan*/  display; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_7__ {int /*<<< orphan*/  gc; int /*<<< orphan*/ * colors; } ;
typedef  TYPE_2__ window_state_t ;
typedef  size_t uint32_t ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_3__ point_t ;

/* Variables and functions */
 int /*<<< orphan*/  XDrawLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XDrawRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _zbar_window_draw_marker (zbar_window_t *w,
                              uint32_t rgb,
                              point_t p)
{
    window_state_t *xs = w->state;
    XSetForeground(w->display, xs->gc, xs->colors[rgb]);
    XDrawRectangle(w->display, w->xwin, xs->gc, p.x - 2, p.y - 2, 4, 4);
    XDrawLine(w->display, w->xwin, xs->gc, p.x, p.y - 3, p.x, p.y + 3);
    XDrawLine(w->display, w->xwin, xs->gc, p.x - 3, p.y, p.x + 3, p.y);
    return(0);
}