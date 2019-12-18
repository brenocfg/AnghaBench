#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  clientInfo_t ;
struct TYPE_13__ {int oldFrame; int frame; float backlerp; scalar_t__ yawing; } ;
struct TYPE_9__ {TYPE_6__ torso; TYPE_6__ legs; } ;
struct TYPE_8__ {int clientNum; int powerups; int legsAnim; int torsoAnim; } ;
struct TYPE_10__ {TYPE_2__ pe; TYPE_1__ currentState; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_12__ {scalar_t__ integer; } ;
struct TYPE_11__ {int /*<<< orphan*/ * clientinfo; } ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int /*<<< orphan*/  CG_RunLerpFrame (int /*<<< orphan*/ *,TYPE_6__*,int,float) ; 
 int LEGS_IDLE ; 
 int LEGS_TURN ; 
 int PW_HASTE ; 
 TYPE_5__ cg_noPlayerAnims ; 
 TYPE_4__ cgs ; 

__attribute__((used)) static void CG_PlayerAnimation( centity_t *cent, int *legsOld, int *legs, float *legsBackLerp,
						int *torsoOld, int *torso, float *torsoBackLerp ) {
	clientInfo_t	*ci;
	int				clientNum;
	float			speedScale;

	clientNum = cent->currentState.clientNum;

	if ( cg_noPlayerAnims.integer ) {
		*legsOld = *legs = *torsoOld = *torso = 0;
		return;
	}

	if ( cent->currentState.powerups & ( 1 << PW_HASTE ) ) {
		speedScale = 1.5;
	} else {
		speedScale = 1;
	}

	ci = &cgs.clientinfo[ clientNum ];

	// do the shuffle turn frames locally
	if ( cent->pe.legs.yawing && ( cent->currentState.legsAnim & ~ANIM_TOGGLEBIT ) == LEGS_IDLE ) {
		CG_RunLerpFrame( ci, &cent->pe.legs, LEGS_TURN, speedScale );
	} else {
		CG_RunLerpFrame( ci, &cent->pe.legs, cent->currentState.legsAnim, speedScale );
	}

	*legsOld = cent->pe.legs.oldFrame;
	*legs = cent->pe.legs.frame;
	*legsBackLerp = cent->pe.legs.backlerp;

	CG_RunLerpFrame( ci, &cent->pe.torso, cent->currentState.torsoAnim, speedScale );

	*torsoOld = cent->pe.torso.oldFrame;
	*torso = cent->pe.torso.frame;
	*torsoBackLerp = cent->pe.torso.backlerp;
}