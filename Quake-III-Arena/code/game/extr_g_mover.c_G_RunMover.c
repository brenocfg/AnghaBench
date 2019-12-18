#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ trType; } ;
struct TYPE_8__ {scalar_t__ trType; } ;
struct TYPE_10__ {TYPE_2__ apos; TYPE_1__ pos; } ;
struct TYPE_11__ {int flags; TYPE_3__ s; } ;
typedef  TYPE_4__ gentity_t ;

/* Variables and functions */
 int FL_TEAMSLAVE ; 
 int /*<<< orphan*/  G_MoverTeam (TYPE_4__*) ; 
 int /*<<< orphan*/  G_RunThink (TYPE_4__*) ; 
 scalar_t__ TR_STATIONARY ; 

void G_RunMover( gentity_t *ent ) {
	// if not a team captain, don't do anything, because
	// the captain will handle everything
	if ( ent->flags & FL_TEAMSLAVE ) {
		return;
	}

	// if stationary at one of the positions, don't move anything
	if ( ent->s.pos.trType != TR_STATIONARY || ent->s.apos.trType != TR_STATIONARY ) {
		G_MoverTeam( ent );
	}

	// check think function
	G_RunThink( ent );
}