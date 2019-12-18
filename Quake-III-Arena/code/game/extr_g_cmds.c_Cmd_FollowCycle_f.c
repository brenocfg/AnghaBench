#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_5__* client; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {int maxclients; TYPE_3__* clients; } ;
struct TYPE_14__ {scalar_t__ sessionTeam; scalar_t__ spectatorState; int spectatorClient; int /*<<< orphan*/  losses; } ;
struct TYPE_15__ {TYPE_4__ sess; } ;
struct TYPE_12__ {scalar_t__ sessionTeam; } ;
struct TYPE_11__ {scalar_t__ connected; } ;
struct TYPE_13__ {TYPE_2__ sess; TYPE_1__ pers; } ;

/* Variables and functions */
 scalar_t__ CON_CONNECTED ; 
 scalar_t__ GT_TOURNAMENT ; 
 int /*<<< orphan*/  G_Error (char*,int) ; 
 scalar_t__ SPECTATOR_FOLLOW ; 
 scalar_t__ SPECTATOR_NOT ; 
 int /*<<< orphan*/  SetTeam (TYPE_6__*,char*) ; 
 scalar_t__ TEAM_FREE ; 
 scalar_t__ TEAM_SPECTATOR ; 
 TYPE_8__ g_gametype ; 
 TYPE_7__ level ; 

void Cmd_FollowCycle_f( gentity_t *ent, int dir ) {
	int		clientnum;
	int		original;

	// if they are playing a tournement game, count as a loss
	if ( (g_gametype.integer == GT_TOURNAMENT )
		&& ent->client->sess.sessionTeam == TEAM_FREE ) {
		ent->client->sess.losses++;
	}
	// first set them to spectator
	if ( ent->client->sess.spectatorState == SPECTATOR_NOT ) {
		SetTeam( ent, "spectator" );
	}

	if ( dir != 1 && dir != -1 ) {
		G_Error( "Cmd_FollowCycle_f: bad dir %i", dir );
	}

	clientnum = ent->client->sess.spectatorClient;
	original = clientnum;
	do {
		clientnum += dir;
		if ( clientnum >= level.maxclients ) {
			clientnum = 0;
		}
		if ( clientnum < 0 ) {
			clientnum = level.maxclients - 1;
		}

		// can only follow connected clients
		if ( level.clients[ clientnum ].pers.connected != CON_CONNECTED ) {
			continue;
		}

		// can't follow another spectator
		if ( level.clients[ clientnum ].sess.sessionTeam == TEAM_SPECTATOR ) {
			continue;
		}

		// this is good, we can use it
		ent->client->sess.spectatorClient = clientnum;
		ent->client->sess.spectatorState = SPECTATOR_FOLLOW;
		return;
	} while ( clientnum != original );

	// leave it where it was
}