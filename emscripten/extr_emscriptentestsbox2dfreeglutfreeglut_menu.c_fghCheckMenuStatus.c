#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ First; } ;
struct TYPE_20__ {int X; int Y; int Width; int Height; TYPE_5__* ActiveEntry; TYPE_4__* Window; void* IsActive; int /*<<< orphan*/  ParentWindow; TYPE_1__ Entries; } ;
struct TYPE_16__ {scalar_t__ Next; } ;
struct TYPE_19__ {int Ordinal; void* IsActive; TYPE_6__* SubMenu; TYPE_2__ Node; } ;
struct TYPE_17__ {int MouseX; int MouseY; void* Redisplay; } ;
struct TYPE_18__ {TYPE_3__ State; TYPE_6__* ActiveMenu; } ;
struct TYPE_14__ {TYPE_4__* CurrentWindow; } ;
typedef  TYPE_4__ SFG_Window ;
typedef  TYPE_5__ SFG_MenuEntry ;
typedef  TYPE_6__ SFG_Menu ;
typedef  void* GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FREEGLUT_INTERNAL_ERROR_EXIT (TYPE_5__*,char*,char*) ; 
 int FREEGLUT_MENU_BORDER ; 
 int FREEGLUT_MENU_HEIGHT ; 
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 int /*<<< orphan*/  fgSetWindow (TYPE_4__*) ; 
 TYPE_11__ fgStructure ; 
 int /*<<< orphan*/  fghDeactivateSubMenu (TYPE_5__*) ; 
 TYPE_5__* fghFindMenuEntry (TYPE_6__*,int) ; 
 int /*<<< orphan*/  fghGetVMaxExtent (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  glutPopWindow () ; 
 int /*<<< orphan*/  glutPositionWindow (int,int) ; 
 int /*<<< orphan*/  glutReshapeWindow (int,int) ; 
 int /*<<< orphan*/  glutShowWindow () ; 

__attribute__((used)) static GLboolean fghCheckMenuStatus( SFG_Menu* menu )
{
    SFG_MenuEntry* menuEntry;
    int x, y;

    /* First of all check any of the active sub menus... */
    for( menuEntry = (SFG_MenuEntry *)menu->Entries.First;
         menuEntry;
         menuEntry = (SFG_MenuEntry *)menuEntry->Node.Next )
    {
        if( menuEntry->SubMenu && menuEntry->IsActive )
        {
            /*
             * OK, have the sub-menu checked, too. If it returns GL_TRUE, it
             * will mean that it caught the mouse cursor and we do not need
             * to regenerate the activity list, and so our parents do...
             */
            GLboolean return_status;

            menuEntry->SubMenu->Window->State.MouseX =
                menu->Window->State.MouseX + menu->X - menuEntry->SubMenu->X;
            menuEntry->SubMenu->Window->State.MouseY =
                menu->Window->State.MouseY + menu->Y - menuEntry->SubMenu->Y;
            return_status = fghCheckMenuStatus( menuEntry->SubMenu );

            if ( return_status )
                return GL_TRUE;
        }
    }

    /* That much about our sub menus, let's get to checking the current menu: */
    x = menu->Window->State.MouseX;
    y = menu->Window->State.MouseY;

    /* Check if the mouse cursor is contained within the current menu box */
    if( ( x >= FREEGLUT_MENU_BORDER ) &&
        ( x < menu->Width  - FREEGLUT_MENU_BORDER ) &&
        ( y >= FREEGLUT_MENU_BORDER ) &&
        ( y < menu->Height - FREEGLUT_MENU_BORDER )  )
    {
        int menuID = ( y - FREEGLUT_MENU_BORDER ) / FREEGLUT_MENU_HEIGHT;

        /* The mouse cursor is somewhere over our box, check it out. */
        menuEntry = fghFindMenuEntry( menu, menuID + 1 );
        FREEGLUT_INTERNAL_ERROR_EXIT( menuEntry, "Cannot find menu entry",
                                      "fghCheckMenuStatus" );

        menuEntry->IsActive = GL_TRUE;
        menuEntry->Ordinal = menuID;

        /*
         * If this is not the same as the last active menu entry, deactivate
         * the previous entry.  Specifically, if the previous active entry
         * was a submenu then deactivate it.
         */
        if( menu->ActiveEntry && ( menuEntry != menu->ActiveEntry ) )
            if( menu->ActiveEntry->SubMenu )
                fghDeactivateSubMenu( menu->ActiveEntry );

        if( menuEntry != menu->ActiveEntry )
        {
            menu->Window->State.Redisplay = GL_TRUE;
            if( menu->ActiveEntry )
                menu->ActiveEntry->IsActive = GL_FALSE;
        }

        menu->ActiveEntry = menuEntry;
        menu->IsActive = GL_TRUE;  /* XXX Do we need this? */

        /*
         * OKi, we have marked that entry as active, but it would be also
         * nice to have its contents updated, in case it's a sub menu.
         * Also, ignore the return value of the check function:
         */
        if( menuEntry->SubMenu )
        {
            if ( ! menuEntry->SubMenu->IsActive )
            {
                int max_x, max_y;
                SFG_Window *current_window = fgStructure.CurrentWindow;

                /* Set up the initial menu position now... */
                menuEntry->SubMenu->IsActive = GL_TRUE;

                /* Set up the initial submenu position now: */
                fghGetVMaxExtent(menu->ParentWindow, &max_x, &max_y);
                menuEntry->SubMenu->X = menu->X + menu->Width;
                menuEntry->SubMenu->Y = menu->Y +
                    menuEntry->Ordinal * FREEGLUT_MENU_HEIGHT;

                if( menuEntry->SubMenu->X + menuEntry->SubMenu->Width > max_x )
                    menuEntry->SubMenu->X = menu->X - menuEntry->SubMenu->Width;

                if( menuEntry->SubMenu->Y + menuEntry->SubMenu->Height > max_y )
                {
                    menuEntry->SubMenu->Y -= ( menuEntry->SubMenu->Height -
                                               FREEGLUT_MENU_HEIGHT -
                                               2 * FREEGLUT_MENU_BORDER );
                    if( menuEntry->SubMenu->Y < 0 )
                        menuEntry->SubMenu->Y = 0;
                }

                fgSetWindow( menuEntry->SubMenu->Window );
                glutPositionWindow( menuEntry->SubMenu->X,
                                    menuEntry->SubMenu->Y );
                glutReshapeWindow( menuEntry->SubMenu->Width,
                                   menuEntry->SubMenu->Height );
                glutPopWindow( );
                glutShowWindow( );
                menuEntry->SubMenu->Window->ActiveMenu = menuEntry->SubMenu;
                fgSetWindow( current_window );
                menuEntry->SubMenu->Window->State.MouseX =
                    x + menu->X - menuEntry->SubMenu->X;
                menuEntry->SubMenu->Window->State.MouseY =
                    y + menu->Y - menuEntry->SubMenu->Y;
                fghCheckMenuStatus( menuEntry->SubMenu );
            }

            /* Activate it because its parent entry is active */
            menuEntry->SubMenu->IsActive = GL_TRUE;  /* XXX Do we need this? */
        }

        /* Report back that we have caught the menu cursor */
        return GL_TRUE;
    }

    /* Looks like the menu cursor is somewhere else... */
    if( menu->ActiveEntry && menu->ActiveEntry->IsActive &&
        ( !menu->ActiveEntry->SubMenu ||
          !menu->ActiveEntry->SubMenu->IsActive ) )
    {
        menu->Window->State.Redisplay = GL_TRUE;
        menu->ActiveEntry->IsActive = GL_FALSE;
        menu->ActiveEntry = NULL;
    }

    return GL_FALSE;
}