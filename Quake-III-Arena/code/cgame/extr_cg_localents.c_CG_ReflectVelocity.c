#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_8__ {scalar_t__* normal; } ;
struct TYPE_9__ {int fraction; TYPE_1__ plane; scalar_t__ allsolid; int /*<<< orphan*/  endpos; } ;
typedef  TYPE_2__ trace_t ;
struct TYPE_12__ {int* trDelta; int trTime; int /*<<< orphan*/  trType; int /*<<< orphan*/  trBase; } ;
struct TYPE_10__ {TYPE_7__ pos; int /*<<< orphan*/  bounceFactor; } ;
typedef  TYPE_3__ localEntity_t ;
struct TYPE_11__ {int time; int frametime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectoryDelta (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TR_STATIONARY ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,scalar_t__*,int*) ; 
 int /*<<< orphan*/  VectorScale (int*,int /*<<< orphan*/ ,int*) ; 
 TYPE_4__ cg ; 

void CG_ReflectVelocity( localEntity_t *le, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	hitTime = cg.time - cg.frametime + cg.frametime * trace->fraction;
	BG_EvaluateTrajectoryDelta( &le->pos, hitTime, velocity );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, le->pos.trDelta );

	VectorScale( le->pos.trDelta, le->bounceFactor, le->pos.trDelta );

	VectorCopy( trace->endpos, le->pos.trBase );
	le->pos.trTime = cg.time;


	// check for stop, making sure that even on low FPS systems it doesn't bobble
	if ( trace->allsolid || 
		( trace->plane.normal[2] > 0 && 
		( le->pos.trDelta[2] < 40 || le->pos.trDelta[2] < -cg.frametime * le->pos.trDelta[2] ) ) ) {
		le->pos.trType = TR_STATIONARY;
	} else {

	}
}