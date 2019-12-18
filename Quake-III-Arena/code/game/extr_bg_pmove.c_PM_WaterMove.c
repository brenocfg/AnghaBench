#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_12__ {int upmove; float forwardmove; float rightmove; } ;
struct TYPE_11__ {scalar_t__ watertype; TYPE_3__* ps; TYPE_6__ cmd; } ;
struct TYPE_7__ {int /*<<< orphan*/  normal; } ;
struct TYPE_8__ {TYPE_1__ plane; } ;
struct TYPE_10__ {float* forward; float* right; TYPE_2__ groundTrace; scalar_t__ groundPlane; } ;
struct TYPE_9__ {int* velocity; float speed; } ;

/* Variables and functions */
 scalar_t__ CONTENTS_SLIME ; 
 scalar_t__ CONTENTS_WATER ; 
 scalar_t__ DotProduct (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVERCLIP ; 
 int /*<<< orphan*/  PM_Accelerate (float*,float,int /*<<< orphan*/ ) ; 
 scalar_t__ PM_CheckWaterJump () ; 
 int /*<<< orphan*/  PM_ClipVelocity (int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 float PM_CmdScale (TYPE_6__*) ; 
 int /*<<< orphan*/  PM_Friction () ; 
 int /*<<< orphan*/  PM_SlideMove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_WaterJumpMove () ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 float VectorLength (int*) ; 
 float VectorNormalize (float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 TYPE_5__* pm ; 
 float pm_swimScale ; 
 int /*<<< orphan*/  pm_wateraccelerate ; 
 TYPE_4__ pml ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void PM_WaterMove( void ) {
	int		i;
	vec3_t	wishvel;
	float	wishspeed;
	vec3_t	wishdir;
	float	scale;
	float	vel;

	if ( PM_CheckWaterJump() ) {
		PM_WaterJumpMove();
		return;
	}
#if 0
	// jump = head for surface
	if ( pm->cmd.upmove >= 10 ) {
		if (pm->ps->velocity[2] > -300) {
			if ( pm->watertype == CONTENTS_WATER ) {
				pm->ps->velocity[2] = 100;
			} else if (pm->watertype == CONTENTS_SLIME) {
				pm->ps->velocity[2] = 80;
			} else {
				pm->ps->velocity[2] = 50;
			}
		}
	}
#endif
	PM_Friction ();

	scale = PM_CmdScale( &pm->cmd );
	//
	// user intentions
	//
	if ( !scale ) {
		wishvel[0] = 0;
		wishvel[1] = 0;
		wishvel[2] = -60;		// sink towards bottom
	} else {
		for (i=0 ; i<3 ; i++)
			wishvel[i] = scale * pml.forward[i]*pm->cmd.forwardmove + scale * pml.right[i]*pm->cmd.rightmove;

		wishvel[2] += scale * pm->cmd.upmove;
	}

	VectorCopy (wishvel, wishdir);
	wishspeed = VectorNormalize(wishdir);

	if ( wishspeed > pm->ps->speed * pm_swimScale ) {
		wishspeed = pm->ps->speed * pm_swimScale;
	}

	PM_Accelerate (wishdir, wishspeed, pm_wateraccelerate);

	// make sure we can go up slopes easily under water
	if ( pml.groundPlane && DotProduct( pm->ps->velocity, pml.groundTrace.plane.normal ) < 0 ) {
		vel = VectorLength(pm->ps->velocity);
		// slide along the ground plane
		PM_ClipVelocity (pm->ps->velocity, pml.groundTrace.plane.normal, 
			pm->ps->velocity, OVERCLIP );

		VectorNormalize(pm->ps->velocity);
		VectorScale(pm->ps->velocity, vel, pm->ps->velocity);
	}

	PM_SlideMove( qfalse );
}