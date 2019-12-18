#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ contents; } ;
struct TYPE_13__ {scalar_t__ event; scalar_t__ loopSound; scalar_t__ modelindex; int /*<<< orphan*/  eType; scalar_t__ eFlags; int /*<<< orphan*/  origin; } ;
struct TYPE_15__ {TYPE_5__ r; TYPE_4__ s; TYPE_3__* client; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_16__ {int /*<<< orphan*/  intermission_angle; int /*<<< orphan*/  intermission_origin; } ;
struct TYPE_11__ {scalar_t__ eFlags; int /*<<< orphan*/  powerups; int /*<<< orphan*/  pm_type; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  origin; } ;
struct TYPE_10__ {scalar_t__ spectatorState; } ;
struct TYPE_12__ {TYPE_2__ ps; TYPE_1__ sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_GENERAL ; 
 int /*<<< orphan*/  PM_INTERMISSION ; 
 scalar_t__ SPECTATOR_FOLLOW ; 
 int /*<<< orphan*/  StopFollowing (TYPE_6__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ level ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void MoveClientToIntermission( gentity_t *ent ) {
	// take out of follow mode if needed
	if ( ent->client->sess.spectatorState == SPECTATOR_FOLLOW ) {
		StopFollowing( ent );
	}


	// move to the spot
	VectorCopy( level.intermission_origin, ent->s.origin );
	VectorCopy( level.intermission_origin, ent->client->ps.origin );
	VectorCopy (level.intermission_angle, ent->client->ps.viewangles);
	ent->client->ps.pm_type = PM_INTERMISSION;

	// clean up powerup info
	memset( ent->client->ps.powerups, 0, sizeof(ent->client->ps.powerups) );

	ent->client->ps.eFlags = 0;
	ent->s.eFlags = 0;
	ent->s.eType = ET_GENERAL;
	ent->s.modelindex = 0;
	ent->s.loopSound = 0;
	ent->s.event = 0;
	ent->r.contents = 0;
}