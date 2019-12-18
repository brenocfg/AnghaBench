#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  powerups; } ;
struct TYPE_12__ {TYPE_2__ s; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_11__ {int ping; scalar_t__* persistant; } ;
struct TYPE_9__ {scalar_t__ connected; int enterTime; } ;
struct TYPE_13__ {int accuracy_shots; int accuracy_hits; TYPE_3__ ps; TYPE_1__ pers; } ;
typedef  TYPE_5__ gclient_t ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_14__ {int numConnectedClients; size_t* sortedClients; int time; int /*<<< orphan*/ * teamScores; TYPE_5__* clients; } ;

/* Variables and functions */
 scalar_t__ CON_CONNECTING ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,size_t,scalar_t__,int,int,int,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__) ; 
 size_t PERS_ASSIST_COUNT ; 
 size_t PERS_CAPTURES ; 
 size_t PERS_DEFEND_COUNT ; 
 size_t PERS_EXCELLENT_COUNT ; 
 size_t PERS_GAUNTLET_FRAG_COUNT ; 
 size_t PERS_IMPRESSIVE_COUNT ; 
 size_t PERS_KILLED ; 
 size_t PERS_RANK ; 
 size_t PERS_SCORE ; 
 size_t TEAM_BLUE ; 
 size_t TEAM_RED ; 
 TYPE_4__* g_entities ; 
 TYPE_6__ level ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void DeathmatchScoreboardMessage( gentity_t *ent ) {
	char		entry[1024];
	char		string[1400];
	int			stringlength;
	int			i, j;
	gclient_t	*cl;
	int			numSorted, scoreFlags, accuracy, perfect;

	// send the latest information on all clients
	string[0] = 0;
	stringlength = 0;
	scoreFlags = 0;

	numSorted = level.numConnectedClients;
	
	for (i=0 ; i < numSorted ; i++) {
		int		ping;

		cl = &level.clients[level.sortedClients[i]];

		if ( cl->pers.connected == CON_CONNECTING ) {
			ping = -1;
		} else {
			ping = cl->ps.ping < 999 ? cl->ps.ping : 999;
		}

		if( cl->accuracy_shots ) {
			accuracy = cl->accuracy_hits * 100 / cl->accuracy_shots;
		}
		else {
			accuracy = 0;
		}
		perfect = ( cl->ps.persistant[PERS_RANK] == 0 && cl->ps.persistant[PERS_KILLED] == 0 ) ? 1 : 0;

		Com_sprintf (entry, sizeof(entry),
			" %i %i %i %i %i %i %i %i %i %i %i %i %i %i", level.sortedClients[i],
			cl->ps.persistant[PERS_SCORE], ping, (level.time - cl->pers.enterTime)/60000,
			scoreFlags, g_entities[level.sortedClients[i]].s.powerups, accuracy, 
			cl->ps.persistant[PERS_IMPRESSIVE_COUNT],
			cl->ps.persistant[PERS_EXCELLENT_COUNT],
			cl->ps.persistant[PERS_GAUNTLET_FRAG_COUNT], 
			cl->ps.persistant[PERS_DEFEND_COUNT], 
			cl->ps.persistant[PERS_ASSIST_COUNT], 
			perfect,
			cl->ps.persistant[PERS_CAPTURES]);
		j = strlen(entry);
		if (stringlength + j > 1024)
			break;
		strcpy (string + stringlength, entry);
		stringlength += j;
	}

	trap_SendServerCommand( ent-g_entities, va("scores %i %i %i%s", i, 
		level.teamScores[TEAM_RED], level.teamScores[TEAM_BLUE],
		string ) );
}