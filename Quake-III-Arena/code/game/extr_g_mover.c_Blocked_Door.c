#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ eType; int /*<<< orphan*/  origin; } ;
struct TYPE_16__ {int spawnflags; scalar_t__ damage; TYPE_2__ s; TYPE_1__* item; int /*<<< orphan*/  client; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_14__ {scalar_t__ giType; } ;

/* Variables and functions */
 scalar_t__ ET_ITEM ; 
 int /*<<< orphan*/  EV_ITEM_POP ; 
 int /*<<< orphan*/  G_Damage (TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_3__*) ; 
 int /*<<< orphan*/  G_TempEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IT_TEAM ; 
 int /*<<< orphan*/  MOD_CRUSH ; 
 int /*<<< orphan*/  Team_DroppedFlagThink (TYPE_3__*) ; 
 int /*<<< orphan*/  Use_BinaryMover (TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 

void Blocked_Door( gentity_t *ent, gentity_t *other ) {
	// remove anything other than a client
	if ( !other->client ) {
		// except CTF flags!!!!
		if( other->s.eType == ET_ITEM && other->item->giType == IT_TEAM ) {
			Team_DroppedFlagThink( other );
			return;
		}
		G_TempEntity( other->s.origin, EV_ITEM_POP );
		G_FreeEntity( other );
		return;
	}

	if ( ent->damage ) {
		G_Damage( other, ent, ent, NULL, NULL, ent->damage, 0, MOD_CRUSH );
	}
	if ( ent->spawnflags & 4 ) {
		return;		// crushers don't reverse
	}

	// reverse direction
	Use_BinaryMover( ent, ent, other );
}