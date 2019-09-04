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

void fgCloseWindow( SFG_Window* window )
{
#if TARGET_HOST_POSIX_X11

    if( window->Window.Context )
        glXDestroyContext( fgDisplay.Display, window->Window.Context );
    XFree( window->Window.FBConfig );
    XDestroyWindow( fgDisplay.Display, window->Window.Handle );
    /* XFlush( fgDisplay.Display ); */ /* XXX Shouldn't need this */

#elif TARGET_HOST_MS_WINDOWS

    /* Make sure we don't close a window with current context active */
    if( fgStructure.CurrentWindow == window )
        wglMakeCurrent( NULL, NULL );

    /*
     * Step through the list of windows.  If the rendering context
     * is not being used by another window, then we delete it.
     */
    {
        int used = FALSE ;
        SFG_Window *iter ;

        for( iter = (SFG_Window *)fgStructure.Windows.First;
             iter;
             iter = (SFG_Window *)iter->Node.Next )
        {
            if( ( iter->Window.Context == window->Window.Context ) &&
                ( iter != window ) )
                used = TRUE;
        }

        if( ! used )
            wglDeleteContext( window->Window.Context );
    }

    DestroyWindow( window->Window.Handle );
#endif
}