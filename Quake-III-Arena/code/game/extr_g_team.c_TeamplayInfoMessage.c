#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  string ;
struct TYPE_17__ {int /*<<< orphan*/  powerups; } ;
struct TYPE_18__ {TYPE_6__ s; TYPE_5__* client; scalar_t__ inuse; } ;
typedef  TYPE_7__ gentity_t ;
typedef  int /*<<< orphan*/  entry ;
typedef  int /*<<< orphan*/  clients ;
struct TYPE_20__ {int integer; } ;
struct TYPE_19__ {int* sortedClients; } ;
struct TYPE_15__ {int* stats; int /*<<< orphan*/  weapon; } ;
struct TYPE_13__ {int /*<<< orphan*/  location; } ;
struct TYPE_14__ {TYPE_2__ teamState; int /*<<< orphan*/  teamInfo; } ;
struct TYPE_12__ {scalar_t__ sessionTeam; } ;
struct TYPE_16__ {TYPE_4__ ps; TYPE_3__ pers; TYPE_1__ sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t STAT_ARMOR ; 
 size_t STAT_HEALTH ; 
 int /*<<< orphan*/  SortClients ; 
 int TEAM_MAXOVERLAY ; 
 TYPE_7__* g_entities ; 
 TYPE_9__ g_maxclients ; 
 TYPE_8__ level ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int,char*) ; 

void TeamplayInfoMessage( gentity_t *ent ) {
	char		entry[1024];
	char		string[8192];
	int			stringlength;
	int			i, j;
	gentity_t	*player;
	int			cnt;
	int			h, a;
	int			clients[TEAM_MAXOVERLAY];

	if ( ! ent->client->pers.teamInfo )
		return;

	// figure out what client should be on the display
	// we are limited to 8, but we want to use the top eight players
	// but in client order (so they don't keep changing position on the overlay)
	for (i = 0, cnt = 0; i < g_maxclients.integer && cnt < TEAM_MAXOVERLAY; i++) {
		player = g_entities + level.sortedClients[i];
		if (player->inuse && player->client->sess.sessionTeam == 
			ent->client->sess.sessionTeam ) {
			clients[cnt++] = level.sortedClients[i];
		}
	}

	// We have the top eight players, sort them by clientNum
	qsort( clients, cnt, sizeof( clients[0] ), SortClients );

	// send the latest information on all clients
	string[0] = 0;
	stringlength = 0;

	for (i = 0, cnt = 0; i < g_maxclients.integer && cnt < TEAM_MAXOVERLAY; i++) {
		player = g_entities + i;
		if (player->inuse && player->client->sess.sessionTeam == 
			ent->client->sess.sessionTeam ) {

			h = player->client->ps.stats[STAT_HEALTH];
			a = player->client->ps.stats[STAT_ARMOR];
			if (h < 0) h = 0;
			if (a < 0) a = 0;

			Com_sprintf (entry, sizeof(entry),
				" %i %i %i %i %i %i", 
//				level.sortedClients[i], player->client->pers.teamState.location, h, a, 
				i, player->client->pers.teamState.location, h, a, 
				player->client->ps.weapon, player->s.powerups);
			j = strlen(entry);
			if (stringlength + j > sizeof(string))
				break;
			strcpy (string + stringlength, entry);
			stringlength += j;
			cnt++;
		}
	}

	trap_SendServerCommand( ent-g_entities, va("tinfo %i %s", cnt, string) );
}