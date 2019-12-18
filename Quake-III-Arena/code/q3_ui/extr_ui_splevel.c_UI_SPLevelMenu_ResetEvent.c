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

/* Variables and functions */
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_ConfirmMenu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_SPLevelMenu_ResetAction ; 
 int /*<<< orphan*/  UI_SPLevelMenu_ResetDraw ; 

__attribute__((used)) static void UI_SPLevelMenu_ResetEvent( void* ptr, int event )
{
	if (event != QM_ACTIVATED) {
		return;
	}

	UI_ConfirmMenu( "RESET GAME?", UI_SPLevelMenu_ResetDraw, UI_SPLevelMenu_ResetAction );
}