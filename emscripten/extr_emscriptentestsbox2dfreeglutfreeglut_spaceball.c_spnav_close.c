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
 int /*<<< orphan*/  DefaultRootWindow (scalar_t__) ; 
 scalar_t__ app_win ; 
 scalar_t__ dpy ; 
 int /*<<< orphan*/  spnav_x11_window (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spnav_close(void)
{
  if(dpy) {
    spnav_x11_window(DefaultRootWindow(dpy));
    app_win = 0;
    dpy = 0;
    return 0;
  }
  return -1;
}