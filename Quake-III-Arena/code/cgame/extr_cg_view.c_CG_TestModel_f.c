#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_5__ {int frame; int /*<<< orphan*/  axis; int /*<<< orphan*/  origin; int /*<<< orphan*/  hModel; scalar_t__ oldframe; int /*<<< orphan*/  backlerp; } ;
struct TYPE_4__ {int /*<<< orphan*/ * viewaxis; int /*<<< orphan*/  vieworg; } ;
struct TYPE_6__ {int /*<<< orphan*/  testGun; TYPE_2__ testModelEntity; scalar_t__* refdefViewAngles; TYPE_1__ refdef; int /*<<< orphan*/  testModelName; } ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Argv (int) ; 
 int /*<<< orphan*/  CG_Printf (char*) ; 
 int /*<<< orphan*/  MAX_QPATH ; 
 size_t PITCH ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ROLL ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t YAW ; 
 int /*<<< orphan*/  atof (int /*<<< orphan*/ ) ; 
 TYPE_3__ cg ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int trap_Argc () ; 
 int /*<<< orphan*/  trap_R_RegisterModel (int /*<<< orphan*/ ) ; 

void CG_TestModel_f (void) {
	vec3_t		angles;

	memset( &cg.testModelEntity, 0, sizeof(cg.testModelEntity) );
	if ( trap_Argc() < 2 ) {
		return;
	}

	Q_strncpyz (cg.testModelName, CG_Argv( 1 ), MAX_QPATH );
	cg.testModelEntity.hModel = trap_R_RegisterModel( cg.testModelName );

	if ( trap_Argc() == 3 ) {
		cg.testModelEntity.backlerp = atof( CG_Argv( 2 ) );
		cg.testModelEntity.frame = 1;
		cg.testModelEntity.oldframe = 0;
	}
	if (! cg.testModelEntity.hModel ) {
		CG_Printf( "Can't register model\n" );
		return;
	}

	VectorMA( cg.refdef.vieworg, 100, cg.refdef.viewaxis[0], cg.testModelEntity.origin );

	angles[PITCH] = 0;
	angles[YAW] = 180 + cg.refdefViewAngles[1];
	angles[ROLL] = 0;

	AnglesToAxis( angles, cg.testModelEntity.axis );
	cg.testGun = qfalse;
}