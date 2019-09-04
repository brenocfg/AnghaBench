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
 scalar_t__ IS_OPEN ; 
 int /*<<< orphan*/  True ; 
 void* XInternAtom (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_win ; 
 void* button_press_event ; 
 void* button_release_event ; 
 void* command_event ; 
 int /*<<< orphan*/ * dpy ; 
 void* motion_event ; 
 int spnav_x11_window (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spnav_x11_open(Display *display, Window win)
{
  if(IS_OPEN) {
    return -1;
  }

  dpy = display;

  motion_event = XInternAtom(dpy, "MotionEvent", True);
  button_press_event = XInternAtom(dpy, "ButtonPressEvent", True);
  button_release_event = XInternAtom(dpy, "ButtonReleaseEvent", True);
  command_event = XInternAtom(dpy, "CommandEvent", True);

  if(!motion_event || !button_press_event || !button_release_event || !command_event) {
    dpy = 0;
    return -1;  /* daemon not started */
  }

  if(spnav_x11_window(win) == -1) {
    dpy = 0;
    return -1;  /* daemon not started */
  }

  app_win = win;
  return 0;
}