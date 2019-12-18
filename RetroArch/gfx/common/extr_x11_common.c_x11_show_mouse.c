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
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  XUndefineCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x11_hide_mouse (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void x11_show_mouse(Display *dpy, Window win, bool state)
{
   if (state)
      XUndefineCursor(dpy, win);
   else
      x11_hide_mouse(dpy, win);
}