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
struct TYPE_4__ {int /*<<< orphan*/  display; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_5__ {scalar_t__ exposed; int /*<<< orphan*/  gc; } ;
typedef  TYPE_2__ window_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  XSetRegion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int _zbar_window_begin (zbar_window_t *w)
{
    window_state_t *xs = w->state;
    if(xs->exposed)
        XSetRegion(w->display, xs->gc, xs->exposed);

    return(0);
}