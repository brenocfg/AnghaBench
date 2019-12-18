#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {TYPE_5__ generic; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {TYPE_3__ generic; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {TYPE_1__ generic; } ;
struct TYPE_16__ {int serverId; int numClients; int phase; int starttime; int numAwards; int won; int lastTier; int scoreboardtime; int /*<<< orphan*/  menu; TYPE_6__ item_menu; TYPE_4__ item_next; TYPE_2__ item_again; scalar_t__ winnerSound; int /*<<< orphan*/ * placeNames; } ;
struct TYPE_15__ {int realtime; scalar_t__ demoversion; } ;

/* Variables and functions */
 int ARENAS_PER_TIER ; 
 int AWARD_PRESENTATION_TIME ; 
 int /*<<< orphan*/  CHAN_ANNOUNCER ; 
 int /*<<< orphan*/  CS_SYSTEMINFO ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 int /*<<< orphan*/  Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 int /*<<< orphan*/  Menu_Draw (int /*<<< orphan*/ *) ; 
 int PROP_HEIGHT ; 
 int /*<<< orphan*/  QMF_INACTIVE ; 
 int SMALLCHAR_HEIGHT ; 
 int /*<<< orphan*/  UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 int /*<<< orphan*/  UI_SPPostgameMenu_DrawAwardsMedals (int) ; 
 int /*<<< orphan*/  UI_SPPostgameMenu_DrawAwardsPresentation (int) ; 
 int /*<<< orphan*/  UI_SPPostgameMenu_MenuDrawScoreLine (int,scalar_t__) ; 
 scalar_t__ UI_ShowTierVideo (int) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_white ; 
 TYPE_8__ postgameMenuInfo ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_Cvar_SetValue (char*,int) ; 
 int /*<<< orphan*/  trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_GetConfigString (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_7__ uis ; 
 char* va (char*,int) ; 

__attribute__((used)) static void UI_SPPostgameMenu_MenuDraw( void ) {
	int		timer;
	int		serverId;
	int		n;
	char	info[MAX_INFO_STRING];

	trap_GetConfigString( CS_SYSTEMINFO, info, sizeof(info) );
	serverId = atoi( Info_ValueForKey( info, "sv_serverid" ) );
	if( serverId != postgameMenuInfo.serverId ) {
		UI_PopMenu();
		return;
	}

	// phase 1
	if ( postgameMenuInfo.numClients > 2 ) {
		UI_DrawProportionalString( 510, 480 - 64 - PROP_HEIGHT, postgameMenuInfo.placeNames[2], UI_CENTER, color_white );
	}
	UI_DrawProportionalString( 130, 480 - 64 - PROP_HEIGHT, postgameMenuInfo.placeNames[1], UI_CENTER, color_white );
	UI_DrawProportionalString( 320, 480 - 64 - 2 * PROP_HEIGHT, postgameMenuInfo.placeNames[0], UI_CENTER, color_white );

	if( postgameMenuInfo.phase == 1 ) {
		timer = uis.realtime - postgameMenuInfo.starttime;

		if( timer >= 1000 && postgameMenuInfo.winnerSound ) {
			trap_S_StartLocalSound( postgameMenuInfo.winnerSound, CHAN_ANNOUNCER );
			postgameMenuInfo.winnerSound = 0;
		}

		if( timer < 5000 ) {
			return;
		}
		postgameMenuInfo.phase = 2;
		postgameMenuInfo.starttime = uis.realtime;
	}

	// phase 2
	if( postgameMenuInfo.phase == 2 ) {
		timer = uis.realtime - postgameMenuInfo.starttime;
		if( timer >= ( postgameMenuInfo.numAwards * AWARD_PRESENTATION_TIME ) ) {

			if( timer < 5000 ) {
				return;
			}

			postgameMenuInfo.phase = 3;
			postgameMenuInfo.starttime = uis.realtime;
		}
		else {
			UI_SPPostgameMenu_DrawAwardsPresentation( timer );
		}
	}

	// phase 3
	if( postgameMenuInfo.phase == 3 ) {
		if( uis.demoversion ) {
			if( postgameMenuInfo.won == 1 && UI_ShowTierVideo( 8 )) {
				trap_Cvar_Set( "nextmap", "" );
				trap_Cmd_ExecuteText( EXEC_APPEND, "disconnect; cinematic demoEnd.RoQ\n" );
				return;
			}
		}
		else if( postgameMenuInfo.won > -1 && UI_ShowTierVideo( postgameMenuInfo.won + 1 )) {
			if( postgameMenuInfo.won == postgameMenuInfo.lastTier ) {
				trap_Cvar_Set( "nextmap", "" );
				trap_Cmd_ExecuteText( EXEC_APPEND, "disconnect; cinematic end.RoQ\n" );
				return;
			}

			trap_Cvar_SetValue( "ui_spSelection", postgameMenuInfo.won * ARENAS_PER_TIER );
			trap_Cvar_Set( "nextmap", "levelselect" );
			trap_Cmd_ExecuteText( EXEC_APPEND, va( "disconnect; cinematic tier%i.RoQ\n", postgameMenuInfo.won + 1 ) );
			return;
		}

		postgameMenuInfo.item_again.generic.flags &= ~QMF_INACTIVE;
		postgameMenuInfo.item_next.generic.flags &= ~QMF_INACTIVE;
		postgameMenuInfo.item_menu.generic.flags &= ~QMF_INACTIVE;

		UI_SPPostgameMenu_DrawAwardsMedals( postgameMenuInfo.numAwards );

		Menu_Draw( &postgameMenuInfo.menu );
	}

	// draw the scoreboard
	if( !trap_Cvar_VariableValue( "ui_spScoreboard" ) ) {
		return;
	}

	timer = uis.realtime - postgameMenuInfo.scoreboardtime;
	if( postgameMenuInfo.numClients <= 3 ) {
		n = 0;
	}
	else {
		n = timer / 1500 % (postgameMenuInfo.numClients + 2);
	}
	UI_SPPostgameMenu_MenuDrawScoreLine( n, 0 );
	UI_SPPostgameMenu_MenuDrawScoreLine( n + 1, 0 + SMALLCHAR_HEIGHT );
	UI_SPPostgameMenu_MenuDrawScoreLine( n + 2, 0 + 2 * SMALLCHAR_HEIGHT );
}