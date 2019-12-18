#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_11__ {int svFlags; } ;
struct TYPE_17__ {TYPE_5__* client; TYPE_1__ r; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_7__ gentity_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_18__ {int maxclients; int numNonSpectatorClients; int* teamScores; size_t* sortedClients; TYPE_3__* clients; int /*<<< orphan*/  time; } ;
struct TYPE_16__ {int* persistant; } ;
struct TYPE_14__ {scalar_t__* persistant; } ;
struct TYPE_15__ {int accuracy_shots; int accuracy_hits; TYPE_4__ ps; } ;
struct TYPE_12__ {size_t sessionTeam; } ;
struct TYPE_13__ {TYPE_6__ ps; TYPE_2__ sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  CalculateRanks () ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int,int,...) ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 scalar_t__ GT_CTF ; 
 int MAX_STRING_CHARS ; 
 size_t PERS_ASSIST_COUNT ; 
 size_t PERS_CAPTURES ; 
 size_t PERS_DEFEND_COUNT ; 
 size_t PERS_EXCELLENT_COUNT ; 
 size_t PERS_GAUNTLET_FRAG_COUNT ; 
 size_t PERS_IMPRESSIVE_COUNT ; 
 size_t PERS_KILLED ; 
 size_t PERS_RANK ; 
 size_t PERS_SCORE ; 
 int SVF_BOT ; 
 size_t TEAM_BLUE ; 
 size_t TEAM_RED ; 
 size_t TEAM_SPECTATOR ; 
 TYPE_7__* g_entities ; 
 TYPE_9__ g_gametype ; 
 TYPE_8__ level ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trap_SendConsoleCommand (int /*<<< orphan*/ ,char*) ; 

void UpdateTournamentInfo( void ) {
	int			i;
	gentity_t	*player;
	int			playerClientNum;
	int			n, accuracy, perfect,	msglen;
	int			buflen;
#ifdef MISSIONPACK // bk001205
  int score1, score2;
	qboolean won;
#endif
	char		buf[32];
	char		msg[MAX_STRING_CHARS];

	// find the real player
	player = NULL;
	for (i = 0; i < level.maxclients; i++ ) {
		player = &g_entities[i];
		if ( !player->inuse ) {
			continue;
		}
		if ( !( player->r.svFlags & SVF_BOT ) ) {
			break;
		}
	}
	// this should never happen!
	if ( !player || i == level.maxclients ) {
		return;
	}
	playerClientNum = i;

	CalculateRanks();

	if ( level.clients[playerClientNum].sess.sessionTeam == TEAM_SPECTATOR ) {
#ifdef MISSIONPACK
		Com_sprintf( msg, sizeof(msg), "postgame %i %i 0 0 0 0 0 0 0 0 0 0 0", level.numNonSpectatorClients, playerClientNum );
#else
		Com_sprintf( msg, sizeof(msg), "postgame %i %i 0 0 0 0 0 0", level.numNonSpectatorClients, playerClientNum );
#endif
	}
	else {
		if( player->client->accuracy_shots ) {
			accuracy = player->client->accuracy_hits * 100 / player->client->accuracy_shots;
		}
		else {
			accuracy = 0;
		}
#ifdef MISSIONPACK
		won = qfalse;
		if (g_gametype.integer >= GT_CTF) {
			score1 = level.teamScores[TEAM_RED];
			score2 = level.teamScores[TEAM_BLUE];
			if (level.clients[playerClientNum].sess.sessionTeam	== TEAM_RED) {
				won = (level.teamScores[TEAM_RED] > level.teamScores[TEAM_BLUE]);
			} else {
				won = (level.teamScores[TEAM_BLUE] > level.teamScores[TEAM_RED]);
			}
		} else {
			if (&level.clients[playerClientNum] == &level.clients[ level.sortedClients[0] ]) {
				won = qtrue;
				score1 = level.clients[ level.sortedClients[0] ].ps.persistant[PERS_SCORE];
				score2 = level.clients[ level.sortedClients[1] ].ps.persistant[PERS_SCORE];
			} else {
				score2 = level.clients[ level.sortedClients[0] ].ps.persistant[PERS_SCORE];
				score1 = level.clients[ level.sortedClients[1] ].ps.persistant[PERS_SCORE];
			}
		}
		if (won && player->client->ps.persistant[PERS_KILLED] == 0) {
			perfect = 1;
		} else {
			perfect = 0;
		}
		Com_sprintf( msg, sizeof(msg), "postgame %i %i %i %i %i %i %i %i %i %i %i %i %i %i", level.numNonSpectatorClients, playerClientNum, accuracy,
			player->client->ps.persistant[PERS_IMPRESSIVE_COUNT], player->client->ps.persistant[PERS_EXCELLENT_COUNT],player->client->ps.persistant[PERS_DEFEND_COUNT],
			player->client->ps.persistant[PERS_ASSIST_COUNT], player->client->ps.persistant[PERS_GAUNTLET_FRAG_COUNT], player->client->ps.persistant[PERS_SCORE],
			perfect, score1, score2, level.time, player->client->ps.persistant[PERS_CAPTURES] );

#else
		perfect = ( level.clients[playerClientNum].ps.persistant[PERS_RANK] == 0 && player->client->ps.persistant[PERS_KILLED] == 0 ) ? 1 : 0;
		Com_sprintf( msg, sizeof(msg), "postgame %i %i %i %i %i %i %i %i", level.numNonSpectatorClients, playerClientNum, accuracy,
			player->client->ps.persistant[PERS_IMPRESSIVE_COUNT], player->client->ps.persistant[PERS_EXCELLENT_COUNT],
			player->client->ps.persistant[PERS_GAUNTLET_FRAG_COUNT], player->client->ps.persistant[PERS_SCORE],
			perfect );
#endif
	}

	msglen = strlen( msg );
	for( i = 0; i < level.numNonSpectatorClients; i++ ) {
		n = level.sortedClients[i];
		Com_sprintf( buf, sizeof(buf), " %i %i %i", n, level.clients[n].ps.persistant[PERS_RANK], level.clients[n].ps.persistant[PERS_SCORE] );
		buflen = strlen( buf );
		if( msglen + buflen + 1 >= sizeof(msg) ) {
			break;
		}
		strcat( msg, buf );
	}
	trap_SendConsoleCommand( EXEC_APPEND, msg );
}