#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ eType; scalar_t__ event; } ;
struct TYPE_19__ {int /*<<< orphan*/  linked; } ;
struct TYPE_21__ {scalar_t__ eventTime; int /*<<< orphan*/  classname; scalar_t__ inuse; TYPE_4__ s; scalar_t__ physicsObject; scalar_t__ neverFree; TYPE_3__ r; scalar_t__ freeAfterEvent; scalar_t__ unlinkAfterEvent; TYPE_2__* client; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_23__ {scalar_t__ integer; } ;
struct TYPE_22__ {int previousTime; int time; int num_entities; int maxclients; int /*<<< orphan*/  framenum; scalar_t__ restarted; } ;
struct TYPE_17__ {scalar_t__ externalEvent; } ;
struct TYPE_18__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CheckCvars () ; 
 int /*<<< orphan*/  CheckExitRules () ; 
 int /*<<< orphan*/  CheckTeamStatus () ; 
 int /*<<< orphan*/  CheckTeamVote (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckTournament () ; 
 int /*<<< orphan*/  CheckVote () ; 
 int /*<<< orphan*/  ClientEndFrame (TYPE_5__*) ; 
 scalar_t__ ET_ITEM ; 
 scalar_t__ ET_MISSILE ; 
 scalar_t__ ET_MOVER ; 
 scalar_t__ EVENT_VALID_MSEC ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_5__*) ; 
 int /*<<< orphan*/  G_Printf (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_RunClient (TYPE_5__*) ; 
 int /*<<< orphan*/  G_RunItem (TYPE_5__*) ; 
 int /*<<< orphan*/  G_RunMissile (TYPE_5__*) ; 
 int /*<<< orphan*/  G_RunMover (TYPE_5__*) ; 
 int /*<<< orphan*/  G_RunThink (TYPE_5__*) ; 
 int /*<<< orphan*/  G_UpdateCvars () ; 
 int MAX_CLIENTS ; 
 int MAX_GENTITIES ; 
 int /*<<< orphan*/  TEAM_BLUE ; 
 int /*<<< orphan*/  TEAM_RED ; 
 TYPE_5__* g_entities ; 
 TYPE_8__ g_listEntity ; 
 TYPE_7__ level ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,char*) ; 
 int trap_Milliseconds () ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_5__*) ; 

void G_RunFrame( int levelTime ) {
	int			i;
	gentity_t	*ent;
	int			msec;
int start, end;

	// if we are waiting for the level to restart, do nothing
	if ( level.restarted ) {
		return;
	}

	level.framenum++;
	level.previousTime = level.time;
	level.time = levelTime;
	msec = level.time - level.previousTime;

	// get any cvar changes
	G_UpdateCvars();

	//
	// go through all allocated objects
	//
	start = trap_Milliseconds();
	ent = &g_entities[0];
	for (i=0 ; i<level.num_entities ; i++, ent++) {
		if ( !ent->inuse ) {
			continue;
		}

		// clear events that are too old
		if ( level.time - ent->eventTime > EVENT_VALID_MSEC ) {
			if ( ent->s.event ) {
				ent->s.event = 0;	// &= EV_EVENT_BITS;
				if ( ent->client ) {
					ent->client->ps.externalEvent = 0;
					// predicted events should never be set to zero
					//ent->client->ps.events[0] = 0;
					//ent->client->ps.events[1] = 0;
				}
			}
			if ( ent->freeAfterEvent ) {
				// tempEntities or dropped items completely go away after their event
				G_FreeEntity( ent );
				continue;
			} else if ( ent->unlinkAfterEvent ) {
				// items that will respawn will hide themselves after their pickup event
				ent->unlinkAfterEvent = qfalse;
				trap_UnlinkEntity( ent );
			}
		}

		// temporary entities don't think
		if ( ent->freeAfterEvent ) {
			continue;
		}

		if ( !ent->r.linked && ent->neverFree ) {
			continue;
		}

		if ( ent->s.eType == ET_MISSILE ) {
			G_RunMissile( ent );
			continue;
		}

		if ( ent->s.eType == ET_ITEM || ent->physicsObject ) {
			G_RunItem( ent );
			continue;
		}

		if ( ent->s.eType == ET_MOVER ) {
			G_RunMover( ent );
			continue;
		}

		if ( i < MAX_CLIENTS ) {
			G_RunClient( ent );
			continue;
		}

		G_RunThink( ent );
	}
end = trap_Milliseconds();

start = trap_Milliseconds();
	// perform final fixups on the players
	ent = &g_entities[0];
	for (i=0 ; i < level.maxclients ; i++, ent++ ) {
		if ( ent->inuse ) {
			ClientEndFrame( ent );
		}
	}
end = trap_Milliseconds();

	// see if it is time to do a tournement restart
	CheckTournament();

	// see if it is time to end the level
	CheckExitRules();

	// update to team status?
	CheckTeamStatus();

	// cancel vote if timed out
	CheckVote();

	// check team votes
	CheckTeamVote( TEAM_RED );
	CheckTeamVote( TEAM_BLUE );

	// for tracking changes
	CheckCvars();

	if (g_listEntity.integer) {
		for (i = 0; i < MAX_GENTITIES; i++) {
			G_Printf("%4i: %s\n", i, g_entities[i].classname);
		}
		trap_Cvar_Set("g_listEntity", "0");
	}
}