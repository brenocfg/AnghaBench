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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  Menu_Cache () ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 char* UI_Argv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_CDKeyMenu_f () ; 
 int /*<<< orphan*/  UI_Cache_f () ; 
 int /*<<< orphan*/  UI_CinematicsMenu_f () ; 
 int /*<<< orphan*/  UI_SPLevelMenu_f () ; 
 int /*<<< orphan*/  UI_SPPostgameMenu_f () ; 
 int /*<<< orphan*/  UI_SPUnlockMedals_f () ; 
 int /*<<< orphan*/  UI_SPUnlock_f () ; 
 int /*<<< orphan*/  UI_TeamOrdersMenu_f () ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean UI_ConsoleCommand( int realTime ) {
	char	*cmd;

	cmd = UI_Argv( 0 );

	// ensure minimum menu data is available
	Menu_Cache();

	if ( Q_stricmp (cmd, "levelselect") == 0 ) {
		UI_SPLevelMenu_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "postgame") == 0 ) {
		UI_SPPostgameMenu_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "ui_cache") == 0 ) {
		UI_Cache_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "ui_cinematics") == 0 ) {
		UI_CinematicsMenu_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "ui_teamOrders") == 0 ) {
		UI_TeamOrdersMenu_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "iamacheater") == 0 ) {
		UI_SPUnlock_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "iamamonkey") == 0 ) {
		UI_SPUnlockMedals_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "ui_cdkey") == 0 ) {
		UI_CDKeyMenu_f();
		return qtrue;
	}

	return qfalse;
}