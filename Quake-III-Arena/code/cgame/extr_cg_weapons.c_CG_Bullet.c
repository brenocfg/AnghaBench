#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {int /*<<< orphan*/  endpos; } ;
typedef  TYPE_1__ trace_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_5__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_Bleed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CG_BubbleTrail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CG_CalcMuzzlePoint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_MissileHitWall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Tracer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  IMPACTSOUND_DEFAULT ; 
 int /*<<< orphan*/  WP_MACHINEGUN ; 
 TYPE_3__ cg_tracerChance ; 
 scalar_t__ random () ; 
 int /*<<< orphan*/  trap_CM_BoxTrace (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int trap_CM_PointContents (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CG_Bullet( vec3_t end, int sourceEntityNum, vec3_t normal, qboolean flesh, int fleshEntityNum ) {
	trace_t trace;
	int sourceContentType, destContentType;
	vec3_t		start;

	// if the shooter is currently valid, calc a source point and possibly
	// do trail effects
	if ( sourceEntityNum >= 0 && cg_tracerChance.value > 0 ) {
		if ( CG_CalcMuzzlePoint( sourceEntityNum, start ) ) {
			sourceContentType = trap_CM_PointContents( start, 0 );
			destContentType = trap_CM_PointContents( end, 0 );

			// do a complete bubble trail if necessary
			if ( ( sourceContentType == destContentType ) && ( sourceContentType & CONTENTS_WATER ) ) {
				CG_BubbleTrail( start, end, 32 );
			}
			// bubble trail from water into air
			else if ( ( sourceContentType & CONTENTS_WATER ) ) {
				trap_CM_BoxTrace( &trace, end, start, NULL, NULL, 0, CONTENTS_WATER );
				CG_BubbleTrail( start, trace.endpos, 32 );
			}
			// bubble trail from air into water
			else if ( ( destContentType & CONTENTS_WATER ) ) {
				trap_CM_BoxTrace( &trace, start, end, NULL, NULL, 0, CONTENTS_WATER );
				CG_BubbleTrail( trace.endpos, end, 32 );
			}

			// draw a tracer
			if ( random() < cg_tracerChance.value ) {
				CG_Tracer( start, end );
			}
		}
	}

	// impact splash and mark
	if ( flesh ) {
		CG_Bleed( end, fleshEntityNum );
	} else {
		CG_MissileHitWall( WP_MACHINEGUN, 0, end, normal, IMPACTSOUND_DEFAULT );
	}

}