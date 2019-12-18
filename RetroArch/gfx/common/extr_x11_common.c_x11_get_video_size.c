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
struct TYPE_3__ {unsigned int width; unsigned int height; } ;
typedef  TYPE_1__ XWindowAttributes ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int DefaultScreen (int /*<<< orphan*/ *) ; 
 unsigned int DisplayHeight (int /*<<< orphan*/ *,int) ; 
 unsigned int DisplayWidth (int /*<<< orphan*/ *,int) ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 scalar_t__ XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 scalar_t__ g_x11_win ; 

void x11_get_video_size(void *data, unsigned *width, unsigned *height)
{
   if (!g_x11_dpy || g_x11_win == None)
   {
      Display *dpy = (Display*)XOpenDisplay(NULL);
      *width       = 0;
      *height      = 0;

      if (dpy)
      {
         int screen = DefaultScreen(dpy);
         *width     = DisplayWidth(dpy, screen);
         *height    = DisplayHeight(dpy, screen);
         XCloseDisplay(dpy);
      }
   }
   else
   {
      XWindowAttributes target;
      XGetWindowAttributes(g_x11_dpy, g_x11_win, &target);

      *width  = target.width;
      *height = target.height;
   }
}