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
typedef  int /*<<< orphan*/  SFG_Window ;

/* Variables and functions */
 int /*<<< orphan*/  fgInitialiseSpaceball () ; 
 int /*<<< orphan*/  sball_initialized ; 

void fgSpaceballSetWindow(SFG_Window *window)
{
    if(!sball_initialized) {
        fgInitialiseSpaceball();
        if(!sball_initialized) {
            return;
        }
    }

#if TARGET_HOST_POSIX_X11
    if(spnav_win != window) {
        spnav_x11_window(window->Window.Handle);
        spnav_win = window;
    }
#endif
}