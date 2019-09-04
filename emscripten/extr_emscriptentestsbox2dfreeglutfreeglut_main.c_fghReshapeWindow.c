#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* CurrentWindow; } ;
struct TYPE_8__ {int /*<<< orphan*/  Redisplay; } ;
struct TYPE_9__ {scalar_t__ IsMenu; TYPE_1__ State; } ;
typedef  TYPE_2__ SFG_Window ;

/* Variables and functions */
 scalar_t__ FETCH_WCB (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  INVOKE_WCB (TYPE_2__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Reshape ; 
 int /*<<< orphan*/  fgSetWindow (TYPE_2__*) ; 
 TYPE_4__ fgStructure ; 
 int /*<<< orphan*/  freeglut_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void fghReshapeWindow ( SFG_Window *window, int width, int height )
{
    SFG_Window *current_window = fgStructure.CurrentWindow;

    freeglut_return_if_fail( window != NULL );


#if TARGET_HOST_POSIX_X11

    XResizeWindow( fgDisplay.Display, window->Window.Handle,
                   width, height );
    XFlush( fgDisplay.Display ); /* XXX Shouldn't need this */

#elif TARGET_HOST_MS_WINDOWS && !defined(_WIN32_WCE)
    {
        RECT winRect;
        int x, y, w, h;

        /*
         * For windowed mode, get the current position of the
         * window and resize taking the size of the frame
         * decorations into account.
         */

        /* "GetWindowRect" returns the pixel coordinates of the outside of the window */
        GetWindowRect( window->Window.Handle, &winRect );
        x = winRect.left;
        y = winRect.top;
        w = width;
        h = height;

        if ( window->Parent == NULL )
        {
            if ( ! window->IsMenu && (window != fgStructure.GameModeWindow) )
            {
                w += GetSystemMetrics( SM_CXSIZEFRAME ) * 2;
                h += GetSystemMetrics( SM_CYSIZEFRAME ) * 2 +
                     GetSystemMetrics( SM_CYCAPTION );
            }
        }
        else
        {
            RECT parentRect;
            GetWindowRect( window->Parent->Window.Handle, &parentRect );
            x -= parentRect.left + GetSystemMetrics( SM_CXSIZEFRAME ) * 2;
            y -= parentRect.top  + GetSystemMetrics( SM_CYSIZEFRAME ) * 2 +
                                   GetSystemMetrics( SM_CYCAPTION );
        }

        /*
         * SWP_NOACTIVATE      Do not activate the window
         * SWP_NOOWNERZORDER   Do not change position in z-order
         * SWP_NOSENDCHANGING  Supress WM_WINDOWPOSCHANGING message
         * SWP_NOZORDER        Retains the current Z order (ignore 2nd param)
         */

        SetWindowPos( window->Window.Handle,
                      HWND_TOP,
                      x, y, w, h,
                      SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING |
                      SWP_NOZORDER
        );
    }
#endif

    /*
     * XXX Should update {window->State.OldWidth, window->State.OldHeight}
     * XXX to keep in lockstep with POSIX_X11 code.
     */
    if( FETCH_WCB( *window, Reshape ) )
        INVOKE_WCB( *window, Reshape, ( width, height ) );
    else
    {
        fgSetWindow( window );
        glViewport( 0, 0, width, height );
    }

    /*
     * Force a window redraw.  In Windows at least this is only a partial
     * solution:  if the window is increasing in size in either dimension,
     * the already-drawn part does not get drawn again and things look funny.
     * But without this we get this bad behaviour whenever we resize the
     * window.
     */
    window->State.Redisplay = GL_TRUE;

    if( window->IsMenu )
        fgSetWindow( current_window );
}