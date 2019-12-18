#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  freq; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ supportedRes_struct ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  RR_Rotate_0 ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XRRConfigCurrentConfiguration (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XRRConfigCurrentRate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XRRFreeScreenConfigInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XRRGetScreenInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XRRSetScreenConfigAndRate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * x11Conf ; 
 int /*<<< orphan*/  x11OriginalRate ; 
 int /*<<< orphan*/  x11OriginalRotation ; 
 int /*<<< orphan*/  x11OriginalSizeId ; 

void ScreenChangeResolution(supportedRes_struct * res)
{
   Display *dpy;
   Window root;

   // Open X11 connection
   dpy = XOpenDisplay(NULL);
   root = RootWindow(dpy, 0);

   if (x11Conf != NULL) XRRFreeScreenConfigInfo(x11Conf);

   // Save original settings
   x11Conf = XRRGetScreenInfo(dpy, root);
   x11OriginalRate = XRRConfigCurrentRate(x11Conf);
   x11OriginalSizeId = XRRConfigCurrentConfiguration(x11Conf, &x11OriginalRotation);

   // Change resolution
   XRRSetScreenConfigAndRate(dpy, x11Conf, root, res->index, RR_Rotate_0, res->freq, CurrentTime);

   // Close connection
   XCloseDisplay(dpy);
}