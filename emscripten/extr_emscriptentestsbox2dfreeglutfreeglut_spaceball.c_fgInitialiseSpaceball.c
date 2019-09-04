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
 int sball_initialized ; 

void fgInitialiseSpaceball(void)
{
    if(sball_initialized) {
        return;
    }

#if TARGET_HOST_POSIX_X11
    {
        Window w;

        if(!fgStructure.CurrentWindow)
            return;

        w = fgStructure.CurrentWindow->Window.Handle;
        if(spnav_x11_open(fgDisplay.Display, w) == -1) {
            return;
        }
    }
#endif

    sball_initialized = 1;
}