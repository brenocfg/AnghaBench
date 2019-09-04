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
struct TYPE_6__ {int /*<<< orphan*/ * display; TYPE_1__* state; scalar_t__ xwin; scalar_t__ window; } ;
typedef  TYPE_2__ zbar_processor_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pre_poll_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  remove_poll (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zbar_window_attach (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int _zbar_processor_close (zbar_processor_t *proc)
{
    if(proc->window)
        zbar_window_attach(proc->window, NULL, 0);

    if(proc->display) {
        if(proc->xwin) {
            XDestroyWindow(proc->display, proc->xwin);
            proc->xwin = 0;
        }
        proc->state->pre_poll_handler = NULL;
        remove_poll(proc, ConnectionNumber(proc->display));
        XCloseDisplay(proc->display);
        proc->display = NULL;
    }
    return(0);
}