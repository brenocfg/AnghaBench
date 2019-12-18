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
typedef  int /*<<< orphan*/  serverinfo ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  map ;
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 int BOT_BEGIN_DELAY_BASE ; 
 int /*<<< orphan*/  CVAR_SERVERINFO ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 char* G_GetArenaInfoByMap (char*) ; 
 int /*<<< orphan*/  G_LoadArenas () ; 
 int /*<<< orphan*/  G_LoadBots () ; 
 int /*<<< orphan*/  G_SpawnBots (char*,int) ; 
 char* Info_ValueForKey (char const*,char*) ; 
 int MAX_INFO_STRING ; 
 int MAX_QPATH ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bot_minplayers ; 
 TYPE_1__ g_gametype ; 
 int /*<<< orphan*/  trap_Cvar_Register (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  trap_GetServerinfo (char*,int) ; 

void G_InitBots( qboolean restart ) {
	int			fragLimit;
	int			timeLimit;
	const char	*arenainfo;
	char		*strValue;
	int			basedelay;
	char		map[MAX_QPATH];
	char		serverinfo[MAX_INFO_STRING];

	G_LoadBots();
	G_LoadArenas();

	trap_Cvar_Register( &bot_minplayers, "bot_minplayers", "0", CVAR_SERVERINFO );

	if( g_gametype.integer == GT_SINGLE_PLAYER ) {
		trap_GetServerinfo( serverinfo, sizeof(serverinfo) );
		Q_strncpyz( map, Info_ValueForKey( serverinfo, "mapname" ), sizeof(map) );
		arenainfo = G_GetArenaInfoByMap( map );
		if ( !arenainfo ) {
			return;
		}

		strValue = Info_ValueForKey( arenainfo, "fraglimit" );
		fragLimit = atoi( strValue );
		if ( fragLimit ) {
			trap_Cvar_Set( "fraglimit", strValue );
		}
		else {
			trap_Cvar_Set( "fraglimit", "0" );
		}

		strValue = Info_ValueForKey( arenainfo, "timelimit" );
		timeLimit = atoi( strValue );
		if ( timeLimit ) {
			trap_Cvar_Set( "timelimit", strValue );
		}
		else {
			trap_Cvar_Set( "timelimit", "0" );
		}

		if ( !fragLimit && !timeLimit ) {
			trap_Cvar_Set( "fraglimit", "10" );
			trap_Cvar_Set( "timelimit", "0" );
		}

		basedelay = BOT_BEGIN_DELAY_BASE;
		strValue = Info_ValueForKey( arenainfo, "special" );
		if( Q_stricmp( strValue, "training" ) == 0 ) {
			basedelay += 10000;
		}

		if( !restart ) {
			G_SpawnBots( Info_ValueForKey( arenainfo, "bots" ), basedelay );
		}
	}
}