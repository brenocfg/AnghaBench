#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_5__* CurrentMenu; TYPE_4__* CurrentWindow; } ;
struct TYPE_17__ {TYPE_4__* ParentWindow; scalar_t__ Y; TYPE_2__* Window; scalar_t__ X; } ;
struct TYPE_15__ {void* Redisplay; } ;
struct TYPE_16__ {TYPE_3__ State; scalar_t__* Menu; int /*<<< orphan*/  IsMenu; TYPE_5__* ActiveMenu; } ;
struct TYPE_13__ {scalar_t__ MouseY; scalar_t__ MouseX; } ;
struct TYPE_14__ {TYPE_1__ State; } ;
typedef  TYPE_4__ SFG_Window ;
typedef  TYPE_5__ SFG_Menu ;
typedef  void* GLboolean ;

/* Variables and functions */
 int FREEGLUT_MAX_MENUS ; 
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 int /*<<< orphan*/  fgDeactivateMenu (TYPE_4__*) ; 
 int /*<<< orphan*/  fgSetWindow (TYPE_4__*) ; 
 TYPE_9__ fgStructure ; 
 int /*<<< orphan*/  fghActivateMenu (TYPE_4__*,int) ; 
 scalar_t__ fghCheckMenuStatus (TYPE_5__*) ; 
 int /*<<< orphan*/  fghExecuteMenuCallback (TYPE_5__*) ; 

GLboolean fgCheckActiveMenu ( SFG_Window *window, int button, GLboolean pressed,
                              int mouse_x, int mouse_y )
{
    /*
     * Near as I can tell, this is the menu behaviour:
     *  - Down-click the menu button, menu not active:  activate
     *    the menu with its upper left-hand corner at the mouse
     *    location.
     *  - Down-click any button outside the menu, menu active:
     *    deactivate the menu
     *  - Down-click any button inside the menu, menu active:
     *    select the menu entry and deactivate the menu
     *  - Up-click the menu button, menu not active:  nothing happens
     *  - Up-click the menu button outside the menu, menu active:
     *    nothing happens
     *  - Up-click the menu button inside the menu, menu active:
     *    select the menu entry and deactivate the menu
     * Since menus can have submenus, we need to check this recursively.
     */
    if( window->ActiveMenu )
    {
        if( window == window->ActiveMenu->ParentWindow )
        {
            window->ActiveMenu->Window->State.MouseX =
                                       mouse_x - window->ActiveMenu->X;
            window->ActiveMenu->Window->State.MouseY =
                                       mouse_y - window->ActiveMenu->Y;
        }

        /* In the menu, invoke the callback and deactivate the menu */
        if( fghCheckMenuStatus( window->ActiveMenu ) )
        {
            /*
             * Save the current window and menu and set the current
             * window to the window whose menu this is
             */
            SFG_Window *save_window = fgStructure.CurrentWindow;
            SFG_Menu *save_menu = fgStructure.CurrentMenu;
            SFG_Window *parent_window = window->ActiveMenu->ParentWindow;
            fgSetWindow( parent_window );
            fgStructure.CurrentMenu = window->ActiveMenu;

            /* Execute the menu callback */
            fghExecuteMenuCallback( window->ActiveMenu );
            fgDeactivateMenu( parent_window );

            /* Restore the current window and menu */
            fgSetWindow( save_window );
            fgStructure.CurrentMenu = save_menu;
        }
        else if( pressed )
            /*
             * Outside the menu, deactivate if it's a downclick
             *
             * XXX This isn't enough.  A downclick outside of
             * XXX the interior of our freeglut windows should also
             * XXX deactivate the menu.  This is more complicated.
             */
            fgDeactivateMenu( window->ActiveMenu->ParentWindow );

        /*
         * XXX Why does an active menu require a redisplay at
         * XXX this point?  If this can come out cleanly, then
         * XXX it probably should do so; if not, a comment should
         * XXX explain it.
         */
        if( ! window->IsMenu )
            window->State.Redisplay = GL_TRUE;

        return GL_TRUE;
    }

    /* No active menu, let's check whether we need to activate one. */
    if( ( 0 <= button ) &&
        ( FREEGLUT_MAX_MENUS > button ) &&
        ( window->Menu[ button ] ) &&
        pressed )
    {
        /* XXX Posting a requisite Redisplay seems bogus. */
        window->State.Redisplay = GL_TRUE;
        fghActivateMenu( window, button );
        return GL_TRUE;
    }

    return GL_FALSE;
}