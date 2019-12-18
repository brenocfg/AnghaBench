#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_13__ {int ping; int /*<<< orphan*/ * persistant; } ;
struct TYPE_11__ {scalar_t__ connected; int /*<<< orphan*/  netname; } ;
struct TYPE_10__ {scalar_t__ sessionTeam; } ;
struct TYPE_14__ {TYPE_4__ ps; TYPE_2__ pers; TYPE_1__ sess; } ;
typedef  TYPE_5__ gclient_t ;
struct TYPE_12__ {int svFlags; } ;
struct TYPE_18__ {TYPE_3__ r; } ;
struct TYPE_17__ {scalar_t__ integer; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {int numConnectedClients; size_t* sortedClients; int /*<<< orphan*/ * teamScores; TYPE_5__* clients; int /*<<< orphan*/  time; int /*<<< orphan*/  intermissionQueued; } ;

/* Variables and functions */
 scalar_t__ CON_CONNECTING ; 
 int /*<<< orphan*/  CS_INTERMISSION ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_TEAM ; 
 scalar_t__ GT_TOURNAMENT ; 
 int /*<<< orphan*/  G_LogPrintf (char*,char const*,...) ; 
 size_t PERS_RANK ; 
 size_t PERS_SCORE ; 
 int SVF_BOT ; 
 size_t TEAM_BLUE ; 
 size_t TEAM_RED ; 
 scalar_t__ TEAM_SPECTATOR ; 
 TYPE_9__* g_entities ; 
 TYPE_8__ g_gametype ; 
 TYPE_7__ g_singlePlayer ; 
 TYPE_6__ level ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_SendConsoleCommand (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trap_SetConfigstring (int /*<<< orphan*/ ,char*) ; 

void LogExit( const char *string ) {
	int				i, numSorted;
	gclient_t		*cl;
#ifdef MISSIONPACK // bk001205
	qboolean won = qtrue;
#endif
	G_LogPrintf( "Exit: %s\n", string );

	level.intermissionQueued = level.time;

	// this will keep the clients from playing any voice sounds
	// that will get cut off when the queued intermission starts
	trap_SetConfigstring( CS_INTERMISSION, "1" );

	// don't send more than 32 scores (FIXME?)
	numSorted = level.numConnectedClients;
	if ( numSorted > 32 ) {
		numSorted = 32;
	}

	if ( g_gametype.integer >= GT_TEAM ) {
		G_LogPrintf( "red:%i  blue:%i\n",
			level.teamScores[TEAM_RED], level.teamScores[TEAM_BLUE] );
	}

	for (i=0 ; i < numSorted ; i++) {
		int		ping;

		cl = &level.clients[level.sortedClients[i]];

		if ( cl->sess.sessionTeam == TEAM_SPECTATOR ) {
			continue;
		}
		if ( cl->pers.connected == CON_CONNECTING ) {
			continue;
		}

		ping = cl->ps.ping < 999 ? cl->ps.ping : 999;

		G_LogPrintf( "score: %i  ping: %i  client: %i %s\n", cl->ps.persistant[PERS_SCORE], ping, level.sortedClients[i],	cl->pers.netname );
#ifdef MISSIONPACK
		if (g_singlePlayer.integer && g_gametype.integer == GT_TOURNAMENT) {
			if (g_entities[cl - level.clients].r.svFlags & SVF_BOT && cl->ps.persistant[PERS_RANK] == 0) {
				won = qfalse;
			}
		}
#endif

	}

#ifdef MISSIONPACK
	if (g_singlePlayer.integer) {
		if (g_gametype.integer >= GT_CTF) {
			won = level.teamScores[TEAM_RED] > level.teamScores[TEAM_BLUE];
		}
		trap_SendConsoleCommand( EXEC_APPEND, (won) ? "spWin\n" : "spLose\n" );
	}
#endif


}