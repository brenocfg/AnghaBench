#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_13__ {TYPE_4__* parent; TYPE_2__* client; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_14__ {scalar_t__ moverState; } ;
struct TYPE_11__ {scalar_t__ sessionTeam; } ;
struct TYPE_12__ {TYPE_1__ sess; } ;

/* Variables and functions */
 scalar_t__ MOVER_1TO2 ; 
 scalar_t__ MOVER_POS2 ; 
 scalar_t__ TEAM_SPECTATOR ; 
 int /*<<< orphan*/  Touch_DoorTriggerSpectator (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Use_BinaryMover (TYPE_4__*,TYPE_3__*,TYPE_3__*) ; 

void Touch_DoorTrigger( gentity_t *ent, gentity_t *other, trace_t *trace ) {
	if ( other->client && other->client->sess.sessionTeam == TEAM_SPECTATOR ) {
		// if the door is not open and not opening
		if ( ent->parent->moverState != MOVER_1TO2 &&
			ent->parent->moverState != MOVER_POS2) {
			Touch_DoorTriggerSpectator( ent, other, trace );
		}
	}
	else if ( ent->parent->moverState != MOVER_1TO2 ) {
		Use_BinaryMover( ent->parent, ent, other );
	}
}