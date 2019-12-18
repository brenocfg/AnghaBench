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
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XRRSetScreenConfigAndRate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * x11Conf ; 
 int /*<<< orphan*/  x11OriginalRate ; 
 int /*<<< orphan*/  x11OriginalRotation ; 
 int /*<<< orphan*/  x11OriginalSizeId ; 

void ScreenRestoreResolution()
{
   Display *dpy;
   Window root;

   if (x11Conf == NULL) return;

   // Open X11 connection
   dpy = XOpenDisplay(NULL);
   root = RootWindow(dpy, 0);
   XRRSetScreenConfigAndRate(dpy, x11Conf, root, x11OriginalSizeId, x11OriginalRotation, x11OriginalRate, CurrentTime);

   // Close connection
   XCloseDisplay(dpy);
}