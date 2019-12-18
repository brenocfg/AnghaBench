#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float* origin; int /*<<< orphan*/  angles; } ;
struct TYPE_8__ {float* maxs; float* mins; } ;
struct TYPE_10__ {float speed; float wait; float* pos2; float* pos1; int /*<<< orphan*/  targetname; struct TYPE_10__* parent; int /*<<< orphan*/  blocked; int /*<<< orphan*/  touch; TYPE_2__ s; TYPE_1__ r; int /*<<< orphan*/  model; int /*<<< orphan*/  damage; void* soundPos2; void* soundPos1; void* sound2to1; void* sound1to2; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  Blocked_Door ; 
 void* G_SoundIndex (char*) ; 
 int /*<<< orphan*/  G_SpawnFloat (char*,char*,float*) ; 
 int /*<<< orphan*/  G_SpawnInt (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitMover (TYPE_3__*) ; 
 int /*<<< orphan*/  SpawnPlatTrigger (TYPE_3__*) ; 
 int /*<<< orphan*/  Touch_Plat ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  trap_SetBrushModel (TYPE_3__*,int /*<<< orphan*/ ) ; 

void SP_func_plat (gentity_t *ent) {
	float		lip, height;

	ent->sound1to2 = ent->sound2to1 = G_SoundIndex("sound/movers/plats/pt1_strt.wav");
	ent->soundPos1 = ent->soundPos2 = G_SoundIndex("sound/movers/plats/pt1_end.wav");

	VectorClear (ent->s.angles);

	G_SpawnFloat( "speed", "200", &ent->speed );
	G_SpawnInt( "dmg", "2", &ent->damage );
	G_SpawnFloat( "wait", "1", &ent->wait );
	G_SpawnFloat( "lip", "8", &lip );

	ent->wait = 1000;

	// create second position
	trap_SetBrushModel( ent, ent->model );

	if ( !G_SpawnFloat( "height", "0", &height ) ) {
		height = (ent->r.maxs[2] - ent->r.mins[2]) - lip;
	}

	// pos1 is the rest (bottom) position, pos2 is the top
	VectorCopy( ent->s.origin, ent->pos2 );
	VectorCopy( ent->pos2, ent->pos1 );
	ent->pos1[2] -= height;

	InitMover( ent );

	// touch function keeps the plat from returning while
	// a live player is standing on it
	ent->touch = Touch_Plat;

	ent->blocked = Blocked_Door;

	ent->parent = ent;	// so it can be treated as a door

	// spawn the trigger if one hasn't been custom made
	if ( !ent->targetname ) {
		SpawnPlatTrigger(ent);
	}
}