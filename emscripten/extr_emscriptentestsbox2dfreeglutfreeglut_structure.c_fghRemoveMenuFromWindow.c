#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Next; } ;
struct TYPE_5__ {scalar_t__ First; } ;
struct TYPE_7__ {TYPE_2__ Node; TYPE_1__ Children; int /*<<< orphan*/ ** Menu; int /*<<< orphan*/ * ActiveMenu; } ;
typedef  TYPE_3__ SFG_Window ;
typedef  int /*<<< orphan*/  SFG_Menu ;

/* Variables and functions */
 int FREEGLUT_MAX_MENUS ; 

__attribute__((used)) static void fghRemoveMenuFromWindow( SFG_Window* window, SFG_Menu* menu )
{
    SFG_Window *subWindow;
    int i;

    /* Check whether this is the active menu in the window */
    if ( menu == window->ActiveMenu )
        window->ActiveMenu = NULL ;

    /*
     * Check if the menu is attached to the current window,
     * if so, have it detached (by overwriting with a NULL):
     */
    for( i = 0; i < FREEGLUT_MAX_MENUS; i++ )
        if( window->Menu[ i ] == menu )
            window->Menu[ i ] = NULL;

    /* Call this function for all of the window's children recursively: */
    for( subWindow = (SFG_Window *)window->Children.First;
         subWindow;
         subWindow = (SFG_Window *)subWindow->Node.Next)
        fghRemoveMenuFromWindow( subWindow, menu );
}