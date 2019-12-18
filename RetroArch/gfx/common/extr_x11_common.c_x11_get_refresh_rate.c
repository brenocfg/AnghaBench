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
struct TYPE_5__ {int /*<<< orphan*/ * screen; } ;
typedef  TYPE_1__ XWindowAttributes ;
struct TYPE_6__ {int flags; float htotal; float vtotal; } ;
typedef  TYPE_2__ XF86VidModeModeLine ;
typedef  int /*<<< orphan*/  Screen ;

/* Variables and functions */
 scalar_t__ None ; 
 int V_DBLSCAN ; 
 int /*<<< orphan*/  XF86VidModeGetModeLine (int /*<<< orphan*/ ,int,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int XScreenNumberOfScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 scalar_t__ g_x11_win ; 

float x11_get_refresh_rate(void *data)
{
   XWindowAttributes attr;
   XF86VidModeModeLine modeline;
   Screen *screen;
   int screenid;
   int dotclock;
   float refresh;

   if (!g_x11_dpy || g_x11_win == None)
      return 0.0f;

   if (!XGetWindowAttributes(g_x11_dpy, g_x11_win, &attr))
      return 0.0f;

   screen = attr.screen;
   screenid = XScreenNumberOfScreen(screen);

   XF86VidModeGetModeLine(g_x11_dpy, screenid, &dotclock, &modeline);

   /* non-native modes like 1080p on a 4K display might use DoubleScan */
   if (modeline.flags & V_DBLSCAN)
      dotclock /= 2;

   refresh = (float)dotclock * 1000.0f / modeline.htotal / modeline.vtotal;

   return refresh;
}