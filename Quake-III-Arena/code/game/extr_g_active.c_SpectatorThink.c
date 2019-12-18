#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int buttons; } ;
typedef  TYPE_4__ usercmd_t ;
struct TYPE_19__ {int tracemask; int /*<<< orphan*/  pointcontents; int /*<<< orphan*/  trace; TYPE_4__ cmd; TYPE_2__* ps; } ;
typedef  TYPE_5__ pmove_t ;
typedef  int /*<<< orphan*/  pm ;
struct TYPE_17__ {int /*<<< orphan*/  origin; } ;
struct TYPE_20__ {TYPE_3__ s; TYPE_7__* client; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_16__ {int speed; int /*<<< orphan*/  origin; int /*<<< orphan*/  pm_type; } ;
struct TYPE_15__ {scalar_t__ spectatorState; } ;
struct TYPE_21__ {int oldbuttons; int buttons; TYPE_2__ ps; TYPE_1__ sess; } ;
typedef  TYPE_7__ gclient_t ;

/* Variables and functions */
 int BUTTON_ATTACK ; 
 int CONTENTS_BODY ; 
 int /*<<< orphan*/  Cmd_FollowCycle_f (TYPE_6__*,int) ; 
 int /*<<< orphan*/  G_TouchTriggers (TYPE_6__*) ; 
 int MASK_PLAYERSOLID ; 
 int /*<<< orphan*/  PM_SPECTATOR ; 
 int /*<<< orphan*/  Pmove (TYPE_5__*) ; 
 scalar_t__ SPECTATOR_FOLLOW ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_PointContents ; 
 int /*<<< orphan*/  trap_Trace ; 
 int /*<<< orphan*/  trap_UnlinkEntity (TYPE_6__*) ; 

void SpectatorThink( gentity_t *ent, usercmd_t *ucmd ) {
	pmove_t	pm;
	gclient_t	*client;

	client = ent->client;

	if ( client->sess.spectatorState != SPECTATOR_FOLLOW ) {
		client->ps.pm_type = PM_SPECTATOR;
		client->ps.speed = 400;	// faster than normal

		// set up for pmove
		memset (&pm, 0, sizeof(pm));
		pm.ps = &client->ps;
		pm.cmd = *ucmd;
		pm.tracemask = MASK_PLAYERSOLID & ~CONTENTS_BODY;	// spectators can fly through bodies
		pm.trace = trap_Trace;
		pm.pointcontents = trap_PointContents;

		// perform a pmove
		Pmove (&pm);
		// save results of pmove
		VectorCopy( client->ps.origin, ent->s.origin );

		G_TouchTriggers( ent );
		trap_UnlinkEntity( ent );
	}

	client->oldbuttons = client->buttons;
	client->buttons = ucmd->buttons;

	// attack button cycles through spectators
	if ( ( client->buttons & BUTTON_ATTACK ) && ! ( client->oldbuttons & BUTTON_ATTACK ) ) {
		Cmd_FollowCycle_f( ent, 1 );
	}
}