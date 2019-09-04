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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  xwin; int /*<<< orphan*/  display; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_5__ {int /*<<< orphan*/  gc; } ;
typedef  TYPE_2__ window_state_t ;

/* Variables and functions */
 int DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhitePixel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XFillRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _zbar_window_clear (zbar_window_t *w)
{
    if(!w->display)
        return(0);
    window_state_t *x = w->state;
    int screen = DefaultScreen(w->display);
    XSetForeground(w->display, x->gc, WhitePixel(w->display, screen));
    XFillRectangle(w->display, w->xwin, x->gc, 0, 0, w->width, w->height);
    return(0);
}