#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Redisplay; scalar_t__ Visible; } ;
struct TYPE_7__ {TYPE_1__ State; } ;
typedef  TYPE_2__ SFG_Window ;
typedef  int /*<<< orphan*/  SFG_Enumerator ;

/* Variables and functions */
 scalar_t__ GL_FALSE ; 
 int /*<<< orphan*/  fgEnumSubWindows (TYPE_2__*,void (*) (TYPE_2__*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fghcbDisplayWindow( SFG_Window *window,
                                SFG_Enumerator *enumerator )
{
    if( window->State.Redisplay &&
        window->State.Visible )
    {
        window->State.Redisplay = GL_FALSE;

#if TARGET_HOST_POSIX_X11
        fghRedrawWindow ( window ) ;
#elif TARGET_HOST_MS_WINDOWS
        RedrawWindow(
            window->Window.Handle, NULL, NULL,
            RDW_NOERASE | RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_UPDATENOW
        );
#endif
    }

    fgEnumSubWindows( window, fghcbDisplayWindow, enumerator );
}