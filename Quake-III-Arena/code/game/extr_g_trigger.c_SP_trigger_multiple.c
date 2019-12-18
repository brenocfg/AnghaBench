#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ wait; scalar_t__ random; int /*<<< orphan*/  use; int /*<<< orphan*/  touch; } ;
typedef  TYPE_1__ gentity_t ;

/* Variables and functions */
 scalar_t__ FRAMETIME ; 
 int /*<<< orphan*/  G_Printf (char*) ; 
 int /*<<< orphan*/  G_SpawnFloat (char*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  InitTrigger (TYPE_1__*) ; 
 int /*<<< orphan*/  Touch_Multi ; 
 int /*<<< orphan*/  Use_Multi ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_1__*) ; 

void SP_trigger_multiple( gentity_t *ent ) {
	G_SpawnFloat( "wait", "0.5", &ent->wait );
	G_SpawnFloat( "random", "0", &ent->random );

	if ( ent->random >= ent->wait && ent->wait >= 0 ) {
		ent->random = ent->wait - FRAMETIME;
		G_Printf( "trigger_multiple has random >= wait\n" );
	}

	ent->touch = Touch_Multi;
	ent->use = Use_Multi;

	InitTrigger( ent );
	trap_LinkEntity (ent);
}