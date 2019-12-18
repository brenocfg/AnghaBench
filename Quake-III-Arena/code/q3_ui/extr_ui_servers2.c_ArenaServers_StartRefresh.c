#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  table_t ;
typedef  int /*<<< orphan*/  protocol ;
struct TYPE_6__ {int curvalue; } ;
struct TYPE_8__ {int maxservers; TYPE_2__ gametype; scalar_t__ refreshtime; scalar_t__ numqueriedservers; scalar_t__* numservers; scalar_t__ nextpingtime; scalar_t__ currentping; int /*<<< orphan*/  refreshservers; TYPE_1__* pinglist; int /*<<< orphan*/  serverlist; } ;
struct TYPE_7__ {scalar_t__ realtime; } ;
struct TYPE_5__ {char* adrstr; } ;

/* Variables and functions */
 scalar_t__ AS_GLOBAL ; 
 scalar_t__ AS_LOCAL ; 
 scalar_t__ AS_MPLAYER ; 
 int /*<<< orphan*/  ArenaServers_UpdateMenu () ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  GAMES_ALL 132 
#define  GAMES_CTF 131 
#define  GAMES_FFA 130 
#define  GAMES_TEAMPLAY 129 
#define  GAMES_TOURNEY 128 
 int MAX_PINGREQUESTS ; 
 TYPE_4__ g_arenaservers ; 
 scalar_t__ g_emptyservers ; 
 scalar_t__ g_fullservers ; 
 scalar_t__ g_servertype ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_Cvar_VariableStringBuffer (char*,char*,int) ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  trap_LAN_ClearPing (int) ; 
 TYPE_3__ uis ; 
 char* va (char*,int,...) ; 

__attribute__((used)) static void ArenaServers_StartRefresh( void )
{
	int		i;
	char	myargs[32], protocol[32];

	memset( g_arenaservers.serverlist, 0, g_arenaservers.maxservers*sizeof(table_t) );

	for (i=0; i<MAX_PINGREQUESTS; i++)
	{
		g_arenaservers.pinglist[i].adrstr[0] = '\0';
		trap_LAN_ClearPing( i );
	}

	g_arenaservers.refreshservers    = qtrue;
	g_arenaservers.currentping       = 0;
	g_arenaservers.nextpingtime      = 0;
	*g_arenaservers.numservers       = 0;
	g_arenaservers.numqueriedservers = 0;

	// allow max 5 seconds for responses
	g_arenaservers.refreshtime = uis.realtime + 5000;

	// place menu in zeroed state
	ArenaServers_UpdateMenu();

	if( g_servertype == AS_LOCAL ) {
		trap_Cmd_ExecuteText( EXEC_APPEND, "localservers\n" );
		return;
	}

	if( g_servertype == AS_GLOBAL || g_servertype == AS_MPLAYER ) {
		if( g_servertype == AS_GLOBAL ) {
			i = 0;
		}
		else {
			i = 1;
		}

		switch( g_arenaservers.gametype.curvalue ) {
		default:
		case GAMES_ALL:
			myargs[0] = 0;
			break;

		case GAMES_FFA:
			strcpy( myargs, " ffa" );
			break;

		case GAMES_TEAMPLAY:
			strcpy( myargs, " team" );
			break;

		case GAMES_TOURNEY:
			strcpy( myargs, " tourney" );
			break;

		case GAMES_CTF:
			strcpy( myargs, " ctf" );
			break;
		}


		if (g_emptyservers) {
			strcat(myargs, " empty");
		}

		if (g_fullservers) {
			strcat(myargs, " full");
		}

		protocol[0] = '\0';
		trap_Cvar_VariableStringBuffer( "debug_protocol", protocol, sizeof(protocol) );
		if (strlen(protocol)) {
			trap_Cmd_ExecuteText( EXEC_APPEND, va( "globalservers %d %s%s\n", i, protocol, myargs ));
		}
		else {
			trap_Cmd_ExecuteText( EXEC_APPEND, va( "globalservers %d %d%s\n", i, (int)trap_Cvar_VariableValue( "protocol" ), myargs ) );
		}
	}
}