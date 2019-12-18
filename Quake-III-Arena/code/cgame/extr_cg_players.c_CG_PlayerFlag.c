#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_22__ {int* lightingOrigin; int /*<<< orphan*/  hModel; int /*<<< orphan*/ * axis; int /*<<< orphan*/  backlerp; int /*<<< orphan*/  frame; int /*<<< orphan*/  oldframe; int /*<<< orphan*/  renderfx; int /*<<< orphan*/  shadowPlane; int /*<<< orphan*/  customSkin; } ;
typedef  TYPE_5__ refEntity_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
typedef  int /*<<< orphan*/  pole ;
typedef  int /*<<< orphan*/  flag ;
typedef  int /*<<< orphan*/  clientInfo_t ;
struct TYPE_17__ {int yawAngle; int /*<<< orphan*/  backlerp; int /*<<< orphan*/  frame; int /*<<< orphan*/  oldFrame; int /*<<< orphan*/  yawing; } ;
struct TYPE_21__ {TYPE_10__ flag; } ;
struct TYPE_19__ {int* trDelta; } ;
struct TYPE_20__ {int legsAnim; size_t clientNum; TYPE_2__ pos; } ;
struct TYPE_23__ {TYPE_4__ pe; TYPE_3__ currentState; } ;
typedef  TYPE_6__ centity_t ;
struct TYPE_18__ {int /*<<< orphan*/  flagFlapModel; int /*<<< orphan*/  flagPoleModel; } ;
struct TYPE_24__ {int /*<<< orphan*/ * clientinfo; TYPE_1__ media; } ;

/* Variables and functions */
 int ANIM_TOGGLEBIT ; 
 int /*<<< orphan*/  AnglesToAxis (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CG_PositionEntityOnTag (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CG_PositionRotatedEntityOnTag (TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CG_RunLerpFrame (int /*<<< orphan*/ *,TYPE_10__*,int,int) ; 
 int /*<<< orphan*/  CG_SwingAngles (int,int,int,float,int*,int /*<<< orphan*/ *) ; 
 float DotProduct (int /*<<< orphan*/ ,int*) ; 
 int FLAG_RUN ; 
 int FLAG_STAND ; 
 int LEGS_IDLE ; 
 int LEGS_IDLECR ; 
 int LEGS_WALK ; 
 int LEGS_WALKCR ; 
 float M_PI ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 size_t YAW ; 
 float acos (float) ; 
 TYPE_9__ cgs ; 
 double fabs (float) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_5__*) ; 

__attribute__((used)) static void CG_PlayerFlag( centity_t *cent, qhandle_t hSkin, refEntity_t *torso ) {
	clientInfo_t	*ci;
	refEntity_t	pole;
	refEntity_t	flag;
	vec3_t		angles, dir;
	int			legsAnim, flagAnim, updateangles;
	float		angle, d;

	// show the flag pole model
	memset( &pole, 0, sizeof(pole) );
	pole.hModel = cgs.media.flagPoleModel;
	VectorCopy( torso->lightingOrigin, pole.lightingOrigin );
	pole.shadowPlane = torso->shadowPlane;
	pole.renderfx = torso->renderfx;
	CG_PositionEntityOnTag( &pole, torso, torso->hModel, "tag_flag" );
	trap_R_AddRefEntityToScene( &pole );

	// show the flag model
	memset( &flag, 0, sizeof(flag) );
	flag.hModel = cgs.media.flagFlapModel;
	flag.customSkin = hSkin;
	VectorCopy( torso->lightingOrigin, flag.lightingOrigin );
	flag.shadowPlane = torso->shadowPlane;
	flag.renderfx = torso->renderfx;

	VectorClear(angles);

	updateangles = qfalse;
	legsAnim = cent->currentState.legsAnim & ~ANIM_TOGGLEBIT;
	if( legsAnim == LEGS_IDLE || legsAnim == LEGS_IDLECR ) {
		flagAnim = FLAG_STAND;
	} else if ( legsAnim == LEGS_WALK || legsAnim == LEGS_WALKCR ) {
		flagAnim = FLAG_STAND;
		updateangles = qtrue;
	} else {
		flagAnim = FLAG_RUN;
		updateangles = qtrue;
	}

	if ( updateangles ) {

		VectorCopy( cent->currentState.pos.trDelta, dir );
		// add gravity
		dir[2] += 100;
		VectorNormalize( dir );
		d = DotProduct(pole.axis[2], dir);
		// if there is anough movement orthogonal to the flag pole
		if (fabs(d) < 0.9) {
			//
			d = DotProduct(pole.axis[0], dir);
			if (d > 1.0f) {
				d = 1.0f;
			}
			else if (d < -1.0f) {
				d = -1.0f;
			}
			angle = acos(d);

			d = DotProduct(pole.axis[1], dir);
			if (d < 0) {
				angles[YAW] = 360 - angle * 180 / M_PI;
			}
			else {
				angles[YAW] = angle * 180 / M_PI;
			}
			if (angles[YAW] < 0)
				angles[YAW] += 360;
			if (angles[YAW] > 360)
				angles[YAW] -= 360;

			//vectoangles( cent->currentState.pos.trDelta, tmpangles );
			//angles[YAW] = tmpangles[YAW] + 45 - cent->pe.torso.yawAngle;
			// change the yaw angle
			CG_SwingAngles( angles[YAW], 25, 90, 0.15f, &cent->pe.flag.yawAngle, &cent->pe.flag.yawing );
		}

		/*
		d = DotProduct(pole.axis[2], dir);
		angle = Q_acos(d);

		d = DotProduct(pole.axis[1], dir);
		if (d < 0) {
			angle = 360 - angle * 180 / M_PI;
		}
		else {
			angle = angle * 180 / M_PI;
		}
		if (angle > 340 && angle < 20) {
			flagAnim = FLAG_RUNUP;
		}
		if (angle > 160 && angle < 200) {
			flagAnim = FLAG_RUNDOWN;
		}
		*/
	}

	// set the yaw angle
	angles[YAW] = cent->pe.flag.yawAngle;
	// lerp the flag animation frames
	ci = &cgs.clientinfo[ cent->currentState.clientNum ];
	CG_RunLerpFrame( ci, &cent->pe.flag, flagAnim, 1 );
	flag.oldframe = cent->pe.flag.oldFrame;
	flag.frame = cent->pe.flag.frame;
	flag.backlerp = cent->pe.flag.backlerp;

	AnglesToAxis( angles, flag.axis );
	CG_PositionRotatedEntityOnTag( &flag, &pole, pole.hModel, "tag_flag" );

	trap_R_AddRefEntityToScene( &flag );
}