#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  spectatorTime; int /*<<< orphan*/  spectatorState; void* sessionTeam; } ;
struct TYPE_10__ {TYPE_2__ sess; } ;
typedef  TYPE_1__ gclient_t ;
typedef  TYPE_2__ clientSession_t ;
struct TYPE_15__ {int integer; } ;
struct TYPE_14__ {int integer; } ;
struct TYPE_13__ {scalar_t__ integer; } ;
struct TYPE_12__ {int numNonSpectatorClients; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BroadcastTeamChange (TYPE_1__*,int) ; 
#define  GT_FFA 130 
#define  GT_SINGLE_PLAYER 129 
 int GT_TEAM ; 
#define  GT_TOURNAMENT 128 
 int /*<<< orphan*/  G_WriteClientSessionData (TYPE_1__*) ; 
 char* Info_ValueForKey (char*,char*) ; 
 void* PickTeam (int) ; 
 int /*<<< orphan*/  SPECTATOR_FREE ; 
 void* TEAM_FREE ; 
 void* TEAM_SPECTATOR ; 
 TYPE_6__ g_gametype ; 
 TYPE_5__ g_maxGameClients ; 
 TYPE_4__ g_teamAutoJoin ; 
 TYPE_3__ level ; 

void G_InitSessionData( gclient_t *client, char *userinfo ) {
	clientSession_t	*sess;
	const char		*value;

	sess = &client->sess;

	// initial team determination
	if ( g_gametype.integer >= GT_TEAM ) {
		if ( g_teamAutoJoin.integer ) {
			sess->sessionTeam = PickTeam( -1 );
			BroadcastTeamChange( client, -1 );
		} else {
			// always spawn as spectator in team games
			sess->sessionTeam = TEAM_SPECTATOR;	
		}
	} else {
		value = Info_ValueForKey( userinfo, "team" );
		if ( value[0] == 's' ) {
			// a willing spectator, not a waiting-in-line
			sess->sessionTeam = TEAM_SPECTATOR;
		} else {
			switch ( g_gametype.integer ) {
			default:
			case GT_FFA:
			case GT_SINGLE_PLAYER:
				if ( g_maxGameClients.integer > 0 && 
					level.numNonSpectatorClients >= g_maxGameClients.integer ) {
					sess->sessionTeam = TEAM_SPECTATOR;
				} else {
					sess->sessionTeam = TEAM_FREE;
				}
				break;
			case GT_TOURNAMENT:
				// if the game is full, go into a waiting mode
				if ( level.numNonSpectatorClients >= 2 ) {
					sess->sessionTeam = TEAM_SPECTATOR;
				} else {
					sess->sessionTeam = TEAM_FREE;
				}
				break;
			}
		}
	}

	sess->spectatorState = SPECTATOR_FREE;
	sess->spectatorTime = level.time;

	G_WriteClientSessionData( client );
}