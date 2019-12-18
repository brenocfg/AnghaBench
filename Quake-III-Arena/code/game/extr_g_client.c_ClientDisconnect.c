#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;

/* Type definitions */
struct TYPE_28__ {int svFlags; } ;
struct TYPE_23__ {scalar_t__ modelindex; int /*<<< orphan*/  clientNum; } ;
struct TYPE_29__ {char* classname; TYPE_8__ r; TYPE_7__* client; int /*<<< orphan*/  inuse; TYPE_3__ s; } ;
typedef  TYPE_9__ gentity_t ;
struct TYPE_26__ {scalar_t__ sessionTeam; } ;
struct TYPE_25__ {void** persistant; int /*<<< orphan*/  origin; } ;
struct TYPE_24__ {scalar_t__ connected; } ;
struct TYPE_27__ {TYPE_6__ sess; TYPE_5__ ps; TYPE_4__ pers; } ;
struct TYPE_21__ {scalar_t__ sessionTeam; scalar_t__ spectatorState; int spectatorClient; int /*<<< orphan*/  wins; } ;
struct TYPE_22__ {TYPE_1__ sess; } ;
struct TYPE_20__ {scalar_t__ integer; } ;
struct TYPE_19__ {int maxclients; int* sortedClients; TYPE_2__* clients; int /*<<< orphan*/  warmupTime; int /*<<< orphan*/  intermissiontime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotAIShutdownClient (int,int /*<<< orphan*/ ) ; 
 scalar_t__ CON_CONNECTED ; 
 scalar_t__ CON_DISCONNECTED ; 
 int CS_PLAYERS ; 
 int /*<<< orphan*/  CalculateRanks () ; 
 int /*<<< orphan*/  ClientUserinfoChanged (size_t) ; 
 int /*<<< orphan*/  EV_PLAYER_TELEPORT_OUT ; 
 scalar_t__ GT_HARVESTER ; 
 scalar_t__ GT_TOURNAMENT ; 
 int /*<<< orphan*/  G_LogPrintf (char*,int) ; 
 int /*<<< orphan*/  G_RemoveQueuedBotBegin (int) ; 
 TYPE_9__* G_TempEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t PERS_TEAM ; 
 scalar_t__ SPECTATOR_FOLLOW ; 
 int SVF_BOT ; 
 int /*<<< orphan*/  StopFollowing (TYPE_9__*) ; 
 void* TEAM_FREE ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/  TossClientCubes (TYPE_9__*) ; 
 int /*<<< orphan*/  TossClientItems (TYPE_9__*) ; 
 int /*<<< orphan*/  TossClientPersistantPowerups (TYPE_9__*) ; 
 TYPE_9__* g_entities ; 
 TYPE_12__ g_gametype ; 
 TYPE_11__ level ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  trap_SetConfigstring (int,char*) ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_9__*) ; 

void ClientDisconnect( int clientNum ) {
	gentity_t	*ent;
	gentity_t	*tent;
	int			i;

	// cleanup if we are kicking a bot that
	// hasn't spawned yet
	G_RemoveQueuedBotBegin( clientNum );

	ent = g_entities + clientNum;
	if ( !ent->client ) {
		return;
	}

	// stop any following clients
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].sess.sessionTeam == TEAM_SPECTATOR
			&& level.clients[i].sess.spectatorState == SPECTATOR_FOLLOW
			&& level.clients[i].sess.spectatorClient == clientNum ) {
			StopFollowing( &g_entities[i] );
		}
	}

	// send effect if they were completely connected
	if ( ent->client->pers.connected == CON_CONNECTED 
		&& ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
		tent = G_TempEntity( ent->client->ps.origin, EV_PLAYER_TELEPORT_OUT );
		tent->s.clientNum = ent->s.clientNum;

		// They don't get to take powerups with them!
		// Especially important for stuff like CTF flags
		TossClientItems( ent );
#ifdef MISSIONPACK
		TossClientPersistantPowerups( ent );
		if( g_gametype.integer == GT_HARVESTER ) {
			TossClientCubes( ent );
		}
#endif

	}

	G_LogPrintf( "ClientDisconnect: %i\n", clientNum );

	// if we are playing in tourney mode and losing, give a win to the other player
	if ( (g_gametype.integer == GT_TOURNAMENT )
		&& !level.intermissiontime
		&& !level.warmupTime && level.sortedClients[1] == clientNum ) {
		level.clients[ level.sortedClients[0] ].sess.wins++;
		ClientUserinfoChanged( level.sortedClients[0] );
	}

	trap_UnlinkEntity (ent);
	ent->s.modelindex = 0;
	ent->inuse = qfalse;
	ent->classname = "disconnected";
	ent->client->pers.connected = CON_DISCONNECTED;
	ent->client->ps.persistant[PERS_TEAM] = TEAM_FREE;
	ent->client->sess.sessionTeam = TEAM_FREE;

	trap_SetConfigstring( CS_PLAYERS + clientNum, "");

	CalculateRanks();

	if ( ent->r.svFlags & SVF_BOT ) {
		BotAIShutdownClient( clientNum, qfalse );
	}
}