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
typedef  int /*<<< orphan*/  voidfunc_f ;
struct TYPE_2__ {int id; } ;
typedef  TYPE_1__ menucommon_s ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  ID_ADDBOTS 137 
#define  ID_LEAVEARENA 136 
#define  ID_QUIT 135 
#define  ID_REMOVEBOTS 134 
#define  ID_RESTART 133 
#define  ID_RESUME 132 
#define  ID_SERVERINFO 131 
#define  ID_SETUP 130 
#define  ID_TEAM 129 
#define  ID_TEAMORDERS 128 
 int /*<<< orphan*/  InGame_QuitAction ; 
 int /*<<< orphan*/  InGame_RestartAction ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_AddBotsMenu () ; 
 int /*<<< orphan*/  UI_ConfirmMenu (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_RemoveBotsMenu () ; 
 int /*<<< orphan*/  UI_ServerInfoMenu () ; 
 int /*<<< orphan*/  UI_SetupMenu () ; 
 int /*<<< orphan*/  UI_TeamMainMenu () ; 
 int /*<<< orphan*/  UI_TeamOrdersMenu () ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 

void InGame_Event( void *ptr, int notification ) {
	if( notification != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_TEAM:
		UI_TeamMainMenu();
		break;

	case ID_SETUP:
		UI_SetupMenu();
		break;

	case ID_LEAVEARENA:
		trap_Cmd_ExecuteText( EXEC_APPEND, "disconnect\n" );
		break;

	case ID_RESTART:
		UI_ConfirmMenu( "RESTART ARENA?", (voidfunc_f)NULL, InGame_RestartAction );
		break;

	case ID_QUIT:
		UI_ConfirmMenu( "EXIT GAME?",  (voidfunc_f)NULL, InGame_QuitAction );
		break;

	case ID_SERVERINFO:
		UI_ServerInfoMenu();
		break;

	case ID_ADDBOTS:
		UI_AddBotsMenu();
		break;

	case ID_REMOVEBOTS:
		UI_RemoveBotsMenu();
		break;

	case ID_TEAMORDERS:
		UI_TeamOrdersMenu();
		break;

	case ID_RESUME:
		UI_PopMenu();
		break;
	}
}