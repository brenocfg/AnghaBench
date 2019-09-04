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
struct TYPE_4__ {int /*<<< orphan*/  display; int /*<<< orphan*/  xwin; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_5__ {int logo_scale; int /*<<< orphan*/  gc; int /*<<< orphan*/  logo_z; int /*<<< orphan*/ * logo_colors; scalar_t__ logo_zbars; scalar_t__ exposed; int /*<<< orphan*/  logo_bars; } ;
typedef  TYPE_2__ window_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BlackPixel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CapButt ; 
 int /*<<< orphan*/  CapRound ; 
 int /*<<< orphan*/  CoordModeOrigin ; 
 int DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JoinMiter ; 
 int /*<<< orphan*/  JoinRound ; 
 int /*<<< orphan*/  LineSolid ; 
 int /*<<< orphan*/  WhitePixel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XDrawLines (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFillRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFillRectangles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XIntersectRegion (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetLineAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int _zbar_window_draw_logo (zbar_window_t *w)
{
    window_state_t *x = w->state;
    int screen = DefaultScreen(w->display);

    /* clear to white */
    XSetForeground(w->display, x->gc, WhitePixel(w->display, screen));
    XFillRectangle(w->display, w->xwin, x->gc, 0, 0, w->width, w->height);

    if(!x->logo_scale || !x->logo_zbars)
        return(0);

    XSetForeground(w->display, x->gc, BlackPixel(w->display, screen));
    XFillRectangles(w->display, w->xwin, x->gc, x->logo_bars, 5);

    XSetLineAttributes(w->display, x->gc, 2 * x->logo_scale,
                       LineSolid, CapRound, JoinRound);

    XSetForeground(w->display, x->gc, x->logo_colors[0]);
    XDrawLines(w->display, w->xwin, x->gc, x->logo_z, 4, CoordModeOrigin);

    if(x->exposed) {
        XIntersectRegion(x->logo_zbars, x->exposed, x->exposed);
        XSetRegion(w->display, x->gc, x->exposed);
    }
    else
        XSetRegion(w->display, x->gc, x->logo_zbars);

    XSetForeground(w->display, x->gc, x->logo_colors[1]);
    XDrawLines(w->display, w->xwin, x->gc, x->logo_z, 4, CoordModeOrigin);

    /* reset GC */
    XSetLineAttributes(w->display, x->gc, 0,
                       LineSolid, CapButt, JoinMiter);
    return(0);
}