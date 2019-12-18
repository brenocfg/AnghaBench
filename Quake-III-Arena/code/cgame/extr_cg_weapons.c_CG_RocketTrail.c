#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  wiTrailTime; int /*<<< orphan*/  trailRadius; } ;
typedef  TYPE_2__ weaponInfo_t ;
typedef  scalar_t__* vec3_t ;
struct TYPE_16__ {int /*<<< orphan*/  leType; } ;
typedef  TYPE_3__ localEntity_t ;
struct TYPE_13__ {scalar_t__ trType; } ;
struct TYPE_17__ {TYPE_12__ pos; } ;
typedef  TYPE_4__ entityState_t ;
struct TYPE_18__ {int trailTime; TYPE_4__ currentState; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_21__ {int time; } ;
struct TYPE_20__ {scalar_t__ integer; } ;
struct TYPE_14__ {int /*<<< orphan*/  smokePuffShader; } ;
struct TYPE_19__ {TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_EvaluateTrajectory (TYPE_12__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  CG_BubbleTrail (scalar_t__*,scalar_t__*,int) ; 
 int CG_PointContents (scalar_t__*,int) ; 
 TYPE_3__* CG_SmokePuff (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int,int,int,float,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  LE_SCALE_FADE ; 
 scalar_t__ TR_STATIONARY ; 
 TYPE_8__ cg ; 
 TYPE_7__ cg_noProjectileTrail ; 
 TYPE_6__ cgs ; 

__attribute__((used)) static void CG_RocketTrail( centity_t *ent, const weaponInfo_t *wi ) {
	int		step;
	vec3_t	origin, lastPos;
	int		t;
	int		startTime, contents;
	int		lastContents;
	entityState_t	*es;
	vec3_t	up;
	localEntity_t	*smoke;

	if ( cg_noProjectileTrail.integer ) {
		return;
	}

	up[0] = 0;
	up[1] = 0;
	up[2] = 0;

	step = 50;

	es = &ent->currentState;
	startTime = ent->trailTime;
	t = step * ( (startTime + step) / step );

	BG_EvaluateTrajectory( &es->pos, cg.time, origin );
	contents = CG_PointContents( origin, -1 );

	// if object (e.g. grenade) is stationary, don't toss up smoke
	if ( es->pos.trType == TR_STATIONARY ) {
		ent->trailTime = cg.time;
		return;
	}

	BG_EvaluateTrajectory( &es->pos, ent->trailTime, lastPos );
	lastContents = CG_PointContents( lastPos, -1 );

	ent->trailTime = cg.time;

	if ( contents & ( CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA ) ) {
		if ( contents & lastContents & CONTENTS_WATER ) {
			CG_BubbleTrail( lastPos, origin, 8 );
		}
		return;
	}

	for ( ; t <= ent->trailTime ; t += step ) {
		BG_EvaluateTrajectory( &es->pos, t, lastPos );

		smoke = CG_SmokePuff( lastPos, up, 
					  wi->trailRadius, 
					  1, 1, 1, 0.33f,
					  wi->wiTrailTime, 
					  t,
					  0,
					  0, 
					  cgs.media.smokePuffShader );
		// use the optimized local entity add
		smoke->leType = LE_SCALE_FADE;
	}

}