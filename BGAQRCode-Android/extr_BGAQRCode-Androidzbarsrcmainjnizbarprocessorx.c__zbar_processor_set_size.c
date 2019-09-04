#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  display; int /*<<< orphan*/  xwin; } ;
typedef  TYPE_1__ zbar_processor_t ;
struct TYPE_6__ {int /*<<< orphan*/  screen; } ;
typedef  TYPE_2__ XWindowAttributes ;

/* Variables and functions */
 int HeightOfScreen (int /*<<< orphan*/ ) ; 
 int WidthOfScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  XResizeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

int _zbar_processor_set_size (zbar_processor_t *proc,
                              unsigned width,
                              unsigned height)
{
    if(!proc->display || !proc->xwin)
        return(0);

    /* refuse to resize greater than (default) screen size */
    XWindowAttributes attr;
    XGetWindowAttributes(proc->display, proc->xwin, &attr);

    int maxw = WidthOfScreen(attr.screen);
    int maxh = HeightOfScreen(attr.screen);
    int w, h;
    if(width > maxw) {
        h = (maxw * height + width - 1) / width;
        w = maxw;
    }
    else {
        w = width;
        h = height;
    }
    if(h > maxh) {
        w = (maxh * width + height - 1) / height;
        h = maxh;
    }
    assert(w <= maxw);
    assert(h <= maxh);

    XResizeWindow(proc->display, proc->xwin, w, h);
    XFlush(proc->display);
    return(0);
}