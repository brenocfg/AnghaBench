#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_8__ {int /*<<< orphan*/  mins; int /*<<< orphan*/  maxs; } ;
struct TYPE_7__ {int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; } ;
struct TYPE_9__ {int speed; int wait; int /*<<< orphan*/  touch; int /*<<< orphan*/  takedamage; scalar_t__ health; int /*<<< orphan*/  pos2; int /*<<< orphan*/ * movedir; int /*<<< orphan*/  pos1; TYPE_2__ r; TYPE_1__ s; int /*<<< orphan*/  model; int /*<<< orphan*/  sound1to2; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_SetMovedir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_SoundIndex (char*) ; 
 int /*<<< orphan*/  G_SpawnFloat (char*,char*,float*) ; 
 int /*<<< orphan*/  InitMover (TYPE_3__*) ; 
 int /*<<< orphan*/  Touch_Button ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 float fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  trap_SetBrushModel (TYPE_3__*,int /*<<< orphan*/ ) ; 

void SP_func_button( gentity_t *ent ) {
	vec3_t		abs_movedir;
	float		distance;
	vec3_t		size;
	float		lip;

	ent->sound1to2 = G_SoundIndex("sound/movers/switches/butn2.wav");
	
	if ( !ent->speed ) {
		ent->speed = 40;
	}

	if ( !ent->wait ) {
		ent->wait = 1;
	}
	ent->wait *= 1000;

	// first position
	VectorCopy( ent->s.origin, ent->pos1 );

	// calculate second position
	trap_SetBrushModel( ent, ent->model );

	G_SpawnFloat( "lip", "4", &lip );

	G_SetMovedir( ent->s.angles, ent->movedir );
	abs_movedir[0] = fabs(ent->movedir[0]);
	abs_movedir[1] = fabs(ent->movedir[1]);
	abs_movedir[2] = fabs(ent->movedir[2]);
	VectorSubtract( ent->r.maxs, ent->r.mins, size );
	distance = abs_movedir[0] * size[0] + abs_movedir[1] * size[1] + abs_movedir[2] * size[2] - lip;
	VectorMA (ent->pos1, distance, ent->movedir, ent->pos2);

	if (ent->health) {
		// shootable button
		ent->takedamage = qtrue;
	} else {
		// touchable button
		ent->touch = Touch_Button;
	}

	InitMover( ent );
}