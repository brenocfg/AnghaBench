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

/* Variables and functions */
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFreeColormap (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ cmap ; 
 int /*<<< orphan*/ * ctx ; 
 int /*<<< orphan*/ * dpy ; 
 int /*<<< orphan*/  glXDestroyContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vi ; 
 int /*<<< orphan*/ * vis ; 
 scalar_t__ wnd ; 

void glewDestroyContext ()
{
  if (NULL != dpy && NULL != ctx) glXDestroyContext(dpy, ctx);
  if (NULL != dpy && 0 != wnd) XDestroyWindow(dpy, wnd);
  if (NULL != dpy && 0 != cmap) XFreeColormap(dpy, cmap);
  if (NULL != vis)
    XFree(vis);
  else if (NULL != vi)
    XFree(vi);
  if (NULL != dpy) XCloseDisplay(dpy);
}