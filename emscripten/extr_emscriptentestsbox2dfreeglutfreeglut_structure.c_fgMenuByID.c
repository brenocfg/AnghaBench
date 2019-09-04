#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ First; } ;
struct TYPE_9__ {TYPE_1__ Menus; } ;
struct TYPE_7__ {scalar_t__ Next; } ;
struct TYPE_8__ {int ID; TYPE_2__ Node; } ;
typedef  TYPE_3__ SFG_Menu ;

/* Variables and functions */
 TYPE_4__ fgStructure ; 

SFG_Menu* fgMenuByID( int menuID )
{
    SFG_Menu *menu = NULL;

    /* It's enough to check all entries in fgStructure.Menus... */
    for( menu = (SFG_Menu *)fgStructure.Menus.First;
         menu;
         menu = (SFG_Menu *)menu->Node.Next )
        if( menu->ID == menuID )
            return menu;
    return NULL;
}