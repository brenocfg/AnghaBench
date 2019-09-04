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
struct TYPE_2__ {scalar_t__ MenuID; scalar_t__ WindowID; int /*<<< orphan*/ * GameModeWindow; int /*<<< orphan*/ * MenuContext; int /*<<< orphan*/ * CurrentMenu; int /*<<< orphan*/ * CurrentWindow; int /*<<< orphan*/  WindowsToDestroy; int /*<<< orphan*/  Menus; int /*<<< orphan*/  Windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  fgListInit (int /*<<< orphan*/ *) ; 
 TYPE_1__ fgStructure ; 

void fgCreateStructure( void )
{
    /*
     * We will be needing two lists: the first containing windows,
     * and the second containing the user-defined menus.
     * Also, no current window/menu is set, as none has been created yet.
     */

    fgListInit(&fgStructure.Windows);
    fgListInit(&fgStructure.Menus);
    fgListInit(&fgStructure.WindowsToDestroy);

    fgStructure.CurrentWindow = NULL;
    fgStructure.CurrentMenu = NULL;
    fgStructure.MenuContext = NULL;
    fgStructure.GameModeWindow = NULL;
    fgStructure.WindowID = 0;
    fgStructure.MenuID = 0;
}