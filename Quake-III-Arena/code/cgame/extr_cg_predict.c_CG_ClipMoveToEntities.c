#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_8__ {scalar_t__ fraction; int entityNum; scalar_t__ allsolid; scalar_t__ startsolid; } ;
typedef  TYPE_1__ trace_t ;
struct TYPE_9__ {int number; int solid; int /*<<< orphan*/  pos; int /*<<< orphan*/  modelindex; } ;
typedef  TYPE_2__ entityState_t ;
typedef  int /*<<< orphan*/  clipHandle_t ;
struct TYPE_10__ {int /*<<< orphan*/  lerpOrigin; TYPE_2__ currentState; int /*<<< orphan*/  lerpAngles; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_11__ {int /*<<< orphan*/  physicsTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int SOLID_BMODEL ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int*) ; 
 TYPE_6__ cg ; 
 int cg_numSolidEntities ; 
 TYPE_3__** cg_solidEntities ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  trap_CM_InlineModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_CM_TempBoxModel (int*,int*) ; 
 int /*<<< orphan*/  trap_CM_TransformedBoxTrace (TYPE_1__*,int* const,int* const,int* const,int* const,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void CG_ClipMoveToEntities ( const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end,
							int skipNumber, int mask, trace_t *tr ) {
	int			i, x, zd, zu;
	trace_t		trace;
	entityState_t	*ent;
	clipHandle_t 	cmodel;
	vec3_t		bmins, bmaxs;
	vec3_t		origin, angles;
	centity_t	*cent;

	for ( i = 0 ; i < cg_numSolidEntities ; i++ ) {
		cent = cg_solidEntities[ i ];
		ent = &cent->currentState;

		if ( ent->number == skipNumber ) {
			continue;
		}

		if ( ent->solid == SOLID_BMODEL ) {
			// special value for bmodel
			cmodel = trap_CM_InlineModel( ent->modelindex );
			VectorCopy( cent->lerpAngles, angles );
			BG_EvaluateTrajectory( &cent->currentState.pos, cg.physicsTime, origin );
		} else {
			// encoded bbox
			x = (ent->solid & 255);
			zd = ((ent->solid>>8) & 255);
			zu = ((ent->solid>>16) & 255) - 32;

			bmins[0] = bmins[1] = -x;
			bmaxs[0] = bmaxs[1] = x;
			bmins[2] = -zd;
			bmaxs[2] = zu;

			cmodel = trap_CM_TempBoxModel( bmins, bmaxs );
			VectorCopy( vec3_origin, angles );
			VectorCopy( cent->lerpOrigin, origin );
		}


		trap_CM_TransformedBoxTrace ( &trace, start, end,
			mins, maxs, cmodel,  mask, origin, angles);

		if (trace.allsolid || trace.fraction < tr->fraction) {
			trace.entityNum = ent->number;
			*tr = trace;
		} else if (trace.startsolid) {
			tr->startsolid = qtrue;
		}
		if ( tr->allsolid ) {
			return;
		}
	}
}