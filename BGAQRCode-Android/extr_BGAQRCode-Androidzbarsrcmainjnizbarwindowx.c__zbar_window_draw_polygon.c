#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_11__ {int /*<<< orphan*/  xwin; int /*<<< orphan*/  display; TYPE_3__ scaled_offset; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_12__ {int /*<<< orphan*/  gc; int /*<<< orphan*/ * colors; } ;
typedef  TYPE_2__ window_state_t ;
typedef  size_t uint32_t ;
typedef  TYPE_3__ point_t ;
struct TYPE_14__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_4__ XPoint ;

/* Variables and functions */
 int /*<<< orphan*/  CoordModeOrigin ; 
 int /*<<< orphan*/  XDrawLines (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ window_scale_pt (TYPE_1__*,TYPE_3__ const) ; 

int _zbar_window_draw_polygon (zbar_window_t *w,
                               uint32_t rgb,
                               const point_t *pts,
                               int npts)
{
    window_state_t *xs = w->state;
    XSetForeground(w->display, xs->gc, xs->colors[rgb]);

    point_t org = w->scaled_offset;
    XPoint xpts[npts + 1];
    int i;
    for(i = 0; i < npts; i++) {
        point_t p = window_scale_pt(w, pts[i]);
        xpts[i].x = p.x + org.x;
        xpts[i].y = p.y + org.y;
    }
    xpts[npts] = xpts[0];

    XDrawLines(w->display, w->xwin, xs->gc, xpts, npts + 1, CoordModeOrigin);

    return(0);
}