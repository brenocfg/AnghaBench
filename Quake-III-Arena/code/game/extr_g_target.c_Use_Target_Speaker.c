#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ loopSound; } ;
struct TYPE_8__ {int spawnflags; scalar_t__ noise_index; TYPE_1__ s; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_GENERAL_SOUND ; 
 int /*<<< orphan*/  EV_GLOBAL_SOUND ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

void Use_Target_Speaker (gentity_t *ent, gentity_t *other, gentity_t *activator) {
	if (ent->spawnflags & 3) {	// looping sound toggles
		if (ent->s.loopSound)
			ent->s.loopSound = 0;	// turn it off
		else
			ent->s.loopSound = ent->noise_index;	// start it
	}else {	// normal sound
		if ( ent->spawnflags & 8 ) {
			G_AddEvent( activator, EV_GENERAL_SOUND, ent->noise_index );
		} else if (ent->spawnflags & 4) {
			G_AddEvent( ent, EV_GLOBAL_SOUND, ent->noise_index );
		} else {
			G_AddEvent( ent, EV_GENERAL_SOUND, ent->noise_index );
		}
	}
}