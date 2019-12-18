#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_11__ {TYPE_3__* client; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_12__ {int /*<<< orphan*/ * teamVoteNo; int /*<<< orphan*/ * teamVoteYes; int /*<<< orphan*/ * teamVoteTime; } ;
struct TYPE_9__ {int eFlags; } ;
struct TYPE_8__ {int sessionTeam; } ;
struct TYPE_10__ {TYPE_2__ ps; TYPE_1__ sess; } ;

/* Variables and functions */
 scalar_t__ CS_TEAMVOTE_NO ; 
 scalar_t__ CS_TEAMVOTE_YES ; 
 int EF_TEAMVOTED ; 
 int TEAM_BLUE ; 
 int TEAM_RED ; 
 int TEAM_SPECTATOR ; 
 int g_entities ; 
 TYPE_6__ level ; 
 int /*<<< orphan*/  trap_Argv (int,char*,int) ; 
 int /*<<< orphan*/  trap_SendServerCommand (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  trap_SetConfigstring (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

void Cmd_TeamVote_f( gentity_t *ent ) {
	int			team, cs_offset;
	char		msg[64];

	team = ent->client->sess.sessionTeam;
	if ( team == TEAM_RED )
		cs_offset = 0;
	else if ( team == TEAM_BLUE )
		cs_offset = 1;
	else
		return;

	if ( !level.teamVoteTime[cs_offset] ) {
		trap_SendServerCommand( ent-g_entities, "print \"No team vote in progress.\n\"" );
		return;
	}
	if ( ent->client->ps.eFlags & EF_TEAMVOTED ) {
		trap_SendServerCommand( ent-g_entities, "print \"Team vote already cast.\n\"" );
		return;
	}
	if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		trap_SendServerCommand( ent-g_entities, "print \"Not allowed to vote as spectator.\n\"" );
		return;
	}

	trap_SendServerCommand( ent-g_entities, "print \"Team vote cast.\n\"" );

	ent->client->ps.eFlags |= EF_TEAMVOTED;

	trap_Argv( 1, msg, sizeof( msg ) );

	if ( msg[0] == 'y' || msg[1] == 'Y' || msg[1] == '1' ) {
		level.teamVoteYes[cs_offset]++;
		trap_SetConfigstring( CS_TEAMVOTE_YES + cs_offset, va("%i", level.teamVoteYes[cs_offset] ) );
	} else {
		level.teamVoteNo[cs_offset]++;
		trap_SetConfigstring( CS_TEAMVOTE_NO + cs_offset, va("%i", level.teamVoteNo[cs_offset] ) );	
	}

	// a majority will be determined in TeamCheckVote, which will also account
	// for players entering or leaving
}