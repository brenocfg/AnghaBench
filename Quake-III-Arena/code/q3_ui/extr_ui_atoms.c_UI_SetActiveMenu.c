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
typedef  int /*<<< orphan*/  voidfunc_f ;
typedef  int uiMenuCommand_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int) ; 
 int /*<<< orphan*/  Menu_Cache () ; 
 int /*<<< orphan*/  NeedCDAction ; 
 int /*<<< orphan*/  NeedCDKeyAction ; 
#define  UIMENU_BAD_CD_KEY 134 
#define  UIMENU_INGAME 133 
#define  UIMENU_MAIN 132 
#define  UIMENU_NEED_CD 131 
#define  UIMENU_NONE 130 
#define  UIMENU_POSTGAME 129 
#define  UIMENU_TEAM 128 
 int /*<<< orphan*/  UI_ConfirmMenu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_ForceMenuOff () ; 
 int /*<<< orphan*/  UI_InGameMenu () ; 
 int /*<<< orphan*/  UI_MainMenu () ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 

void UI_SetActiveMenu( uiMenuCommand_t menu ) {
	// this should be the ONLY way the menu system is brought up
	// enusure minumum menu data is cached
	Menu_Cache();

	switch ( menu ) {
	case UIMENU_NONE:
		UI_ForceMenuOff();
		return;
	case UIMENU_MAIN:
		UI_MainMenu();
		return;
	case UIMENU_NEED_CD:
		UI_ConfirmMenu( "Insert the CD", (voidfunc_f)NULL, NeedCDAction );
		return;
	case UIMENU_BAD_CD_KEY:
		UI_ConfirmMenu( "Bad CD Key", (voidfunc_f)NULL, NeedCDKeyAction );
		return;
	case UIMENU_INGAME:
		/*
		//GRank
		UI_RankingsMenu();
		return;
		*/
		trap_Cvar_Set( "cl_paused", "1" );
		UI_InGameMenu();
		return;
		
	// bk001204
	case UIMENU_TEAM:
	case UIMENU_POSTGAME:
	default:
#ifndef NDEBUG
	  Com_Printf("UI_SetActiveMenu: bad enum %d\n", menu );
#endif
	  break;
	}
}