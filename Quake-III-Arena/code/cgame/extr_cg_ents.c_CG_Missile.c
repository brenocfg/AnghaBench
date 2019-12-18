#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int missileRenderfx; int /*<<< orphan*/  missileModel; scalar_t__ missileSound; int /*<<< orphan*/ * missileDlightColor; scalar_t__ missileDlight; int /*<<< orphan*/  (* missileTrailFunc ) (TYPE_5__*,TYPE_2__ const*) ;} ;
typedef  TYPE_2__ weaponInfo_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_22__ {int radius; int skinNum; int renderfx; int** axis; int /*<<< orphan*/  hModel; int /*<<< orphan*/  customShader; scalar_t__ rotation; int /*<<< orphan*/  reType; int /*<<< orphan*/  oldorigin; int /*<<< orphan*/  origin; } ;
typedef  TYPE_3__ refEntity_t ;
struct TYPE_19__ {scalar_t__ trType; int /*<<< orphan*/  trDelta; } ;
struct TYPE_23__ {size_t weapon; scalar_t__ generic1; int time; TYPE_16__ pos; int /*<<< orphan*/  number; int /*<<< orphan*/  angles; } ;
typedef  TYPE_4__ entityState_t ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_24__ {int /*<<< orphan*/  lerpAngles; TYPE_4__ currentState; int /*<<< orphan*/  lerpOrigin; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_20__ {int /*<<< orphan*/  blueProxMine; int /*<<< orphan*/  plasmaBallShader; } ;
struct TYPE_18__ {int time; int clientFrame; } ;
struct TYPE_17__ {TYPE_1__ media; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  BG_EvaluateTrajectoryDelta (TYPE_16__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_AddRefEntityWithPowerups (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int RF_NOSHADOW ; 
 int /*<<< orphan*/  RT_SPRITE ; 
 int /*<<< orphan*/  RotateAroundDirection (int**,int) ; 
 scalar_t__ TEAM_BLUE ; 
 int /*<<< orphan*/  TEAM_FREE ; 
 scalar_t__ TR_STATIONARY ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VectorNormalize2 (int /*<<< orphan*/ ,int*) ; 
 size_t WP_NUM_WEAPONS ; 
 scalar_t__ WP_PLASMAGUN ; 
 size_t WP_PROX_LAUNCHER ; 
 TYPE_12__ cg ; 
 TYPE_2__* cg_weapons ; 
 TYPE_10__ cgs ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  trap_R_AddLightToScene (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_3__*) ; 
 int /*<<< orphan*/  trap_S_AddLoopingSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void CG_Missile( centity_t *cent ) {
	refEntity_t			ent;
	entityState_t		*s1;
	const weaponInfo_t		*weapon;
//	int	col;

	s1 = &cent->currentState;
	if ( s1->weapon > WP_NUM_WEAPONS ) {
		s1->weapon = 0;
	}
	weapon = &cg_weapons[s1->weapon];

	// calculate the axis
	VectorCopy( s1->angles, cent->lerpAngles);

	// add trails
	if ( weapon->missileTrailFunc ) 
	{
		weapon->missileTrailFunc( cent, weapon );
	}
/*
	if ( cent->currentState.modelindex == TEAM_RED ) {
		col = 1;
	}
	else if ( cent->currentState.modelindex == TEAM_BLUE ) {
		col = 2;
	}
	else {
		col = 0;
	}

	// add dynamic light
	if ( weapon->missileDlight ) {
		trap_R_AddLightToScene(cent->lerpOrigin, weapon->missileDlight, 
			weapon->missileDlightColor[col][0], weapon->missileDlightColor[col][1], weapon->missileDlightColor[col][2] );
	}
*/
	// add dynamic light
	if ( weapon->missileDlight ) {
		trap_R_AddLightToScene(cent->lerpOrigin, weapon->missileDlight, 
			weapon->missileDlightColor[0], weapon->missileDlightColor[1], weapon->missileDlightColor[2] );
	}

	// add missile sound
	if ( weapon->missileSound ) {
		vec3_t	velocity;

		BG_EvaluateTrajectoryDelta( &cent->currentState.pos, cg.time, velocity );

		trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, velocity, weapon->missileSound );
	}

	// create the render entity
	memset (&ent, 0, sizeof(ent));
	VectorCopy( cent->lerpOrigin, ent.origin);
	VectorCopy( cent->lerpOrigin, ent.oldorigin);

	if ( cent->currentState.weapon == WP_PLASMAGUN ) {
		ent.reType = RT_SPRITE;
		ent.radius = 16;
		ent.rotation = 0;
		ent.customShader = cgs.media.plasmaBallShader;
		trap_R_AddRefEntityToScene( &ent );
		return;
	}

	// flicker between two skins
	ent.skinNum = cg.clientFrame & 1;
	ent.hModel = weapon->missileModel;
	ent.renderfx = weapon->missileRenderfx | RF_NOSHADOW;

#ifdef MISSIONPACK
	if ( cent->currentState.weapon == WP_PROX_LAUNCHER ) {
		if (s1->generic1 == TEAM_BLUE) {
			ent.hModel = cgs.media.blueProxMine;
		}
	}
#endif

	// convert direction of travel into axis
	if ( VectorNormalize2( s1->pos.trDelta, ent.axis[0] ) == 0 ) {
		ent.axis[0][2] = 1;
	}

	// spin as it moves
	if ( s1->pos.trType != TR_STATIONARY ) {
		RotateAroundDirection( ent.axis, cg.time / 4 );
	} else {
#ifdef MISSIONPACK
		if ( s1->weapon == WP_PROX_LAUNCHER ) {
			AnglesToAxis( cent->lerpAngles, ent.axis );
		}
		else
#endif
		{
			RotateAroundDirection( ent.axis, s1->time );
		}
	}

	// add to refresh list, possibly with quad glow
	CG_AddRefEntityWithPowerups( &ent, s1, TEAM_FREE );
}