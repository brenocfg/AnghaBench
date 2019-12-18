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
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  mapname ;
typedef  int /*<<< orphan*/  expanded ;
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 int CVAR_LATCH ; 
 int CVAR_SERVERINFO ; 
 int CVAR_USERINFO ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  Cvar_Get (char*,char*,int) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  Cvar_SetLatched (char*,char*) ; 
 int /*<<< orphan*/  Cvar_SetValue (char*,scalar_t__) ; 
 int FS_ReadFile (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ GT_FFA ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 scalar_t__ Q_stricmpn (char*,char*,int) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  SV_SpawnServer (char*,scalar_t__) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 TYPE_1__* sv_gametype ; 

__attribute__((used)) static void SV_Map_f( void ) {
	char		*cmd;
	char		*map;
	qboolean	killBots, cheat;
	char		expanded[MAX_QPATH];
	char		mapname[MAX_QPATH];

	map = Cmd_Argv(1);
	if ( !map ) {
		return;
	}

	// make sure the level exists before trying to change, so that
	// a typo at the server console won't end the game
	Com_sprintf (expanded, sizeof(expanded), "maps/%s.bsp", map);
	if ( FS_ReadFile (expanded, NULL) == -1 ) {
		Com_Printf ("Can't find map %s\n", expanded);
		return;
	}

	// force latched values to get set
	Cvar_Get ("g_gametype", "0", CVAR_SERVERINFO | CVAR_USERINFO | CVAR_LATCH );

	cmd = Cmd_Argv(0);
	if( Q_stricmpn( cmd, "sp", 2 ) == 0 ) {
		Cvar_SetValue( "g_gametype", GT_SINGLE_PLAYER );
		Cvar_SetValue( "g_doWarmup", 0 );
		// may not set sv_maxclients directly, always set latched
		Cvar_SetLatched( "sv_maxclients", "8" );
		cmd += 2;
		cheat = qfalse;
		killBots = qtrue;
	}
	else {
		if ( !Q_stricmp( cmd, "devmap" ) || !Q_stricmp( cmd, "spdevmap" ) ) {
			cheat = qtrue;
			killBots = qtrue;
		} else {
			cheat = qfalse;
			killBots = qfalse;
		}
		if( sv_gametype->integer == GT_SINGLE_PLAYER ) {
			Cvar_SetValue( "g_gametype", GT_FFA );
		}
	}

	// save the map name here cause on a map restart we reload the q3config.cfg
	// and thus nuke the arguments of the map command
	Q_strncpyz(mapname, map, sizeof(mapname));

	// start up the map
	SV_SpawnServer( mapname, killBots );

	// set the cheat value
	// if the level was started with "map <levelname>", then
	// cheats will not be allowed.  If started with "devmap <levelname>"
	// then cheats will be allowed
	if ( cheat ) {
		Cvar_Set( "sv_cheats", "1" );
	} else {
		Cvar_Set( "sv_cheats", "0" );
	}
}