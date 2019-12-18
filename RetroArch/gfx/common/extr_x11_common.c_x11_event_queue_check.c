#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  XEvent ;

/* Variables and functions */
 int /*<<< orphan*/  XIfEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 int /*<<< orphan*/  x11_wait_notify ; 

void x11_event_queue_check(XEvent *event)
{
   XIfEvent(g_x11_dpy, event, x11_wait_notify, NULL);
}