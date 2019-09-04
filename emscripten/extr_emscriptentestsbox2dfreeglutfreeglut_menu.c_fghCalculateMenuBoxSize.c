#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* CurrentMenu; } ;
struct TYPE_6__ {scalar_t__ First; } ;
struct TYPE_9__ {int Height; int Width; TYPE_1__ Entries; } ;
struct TYPE_7__ {scalar_t__ Next; } ;
struct TYPE_8__ {int Width; scalar_t__ SubMenu; scalar_t__ Text; TYPE_2__ Node; } ;
typedef  TYPE_3__ SFG_MenuEntry ;

/* Variables and functions */
 int FREEGLUT_MENU_BORDER ; 
 int /*<<< orphan*/  FREEGLUT_MENU_FONT ; 
 scalar_t__ FREEGLUT_MENU_HEIGHT ; 
 TYPE_5__ fgStructure ; 
 int /*<<< orphan*/  freeglut_return_if_fail (TYPE_4__*) ; 
 int glutBitmapLength (int /*<<< orphan*/ ,unsigned char*) ; 

void fghCalculateMenuBoxSize( void )
{
    SFG_MenuEntry* menuEntry;
    int width = 0, height = 0;

    /* Make sure there is a current menu set */
    freeglut_return_if_fail( fgStructure.CurrentMenu );

    /* The menu's box size depends on the menu entries: */
    for( menuEntry = ( SFG_MenuEntry * )fgStructure.CurrentMenu->Entries.First;
         menuEntry;
         menuEntry = ( SFG_MenuEntry * )menuEntry->Node.Next )
    {
        /* Update the menu entry's width value */
        menuEntry->Width = glutBitmapLength(
            FREEGLUT_MENU_FONT,
            (unsigned char *)menuEntry->Text
        );

        /*
         * If the entry is a submenu, then it needs to be wider to
         * accomodate the arrow. JCJ 31 July 2003
         */
        if (menuEntry->SubMenu )
            menuEntry->Width += glutBitmapLength(
                FREEGLUT_MENU_FONT,
                (unsigned char *)"_"
            );

        /* Check if it's the biggest we've found */
        if( menuEntry->Width > width )
            width = menuEntry->Width;

        height += FREEGLUT_MENU_HEIGHT;
    }

    /* Store the menu's box size now: */
    fgStructure.CurrentMenu->Height = height + 2 * FREEGLUT_MENU_BORDER;
    fgStructure.CurrentMenu->Width  = width  + 4 * FREEGLUT_MENU_BORDER;
}