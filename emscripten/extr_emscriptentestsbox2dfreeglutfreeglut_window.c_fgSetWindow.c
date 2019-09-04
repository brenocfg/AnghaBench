#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * CurrentWindow; } ;
typedef  int /*<<< orphan*/  SFG_Window ;

/* Variables and functions */
 TYPE_1__ fgStructure ; 

void fgSetWindow ( SFG_Window *window )
{
#if TARGET_HOST_POSIX_X11
    if ( window )
    {
        glXMakeContextCurrent(
            fgDisplay.Display,
            window->Window.Handle,
            window->Window.Handle,
            window->Window.Context
        );

        /* also register this window to receive spaceball events */
        fgSpaceballSetWindow(window);
    }
#elif TARGET_HOST_MS_WINDOWS
    if( fgStructure.CurrentWindow )
        ReleaseDC( fgStructure.CurrentWindow->Window.Handle,
                   fgStructure.CurrentWindow->Window.Device );

    if ( window )
    {
        window->Window.Device = GetDC( window->Window.Handle );
        wglMakeCurrent(
            window->Window.Device,
            window->Window.Context
        );
    }
#endif
    fgStructure.CurrentWindow = window;
}