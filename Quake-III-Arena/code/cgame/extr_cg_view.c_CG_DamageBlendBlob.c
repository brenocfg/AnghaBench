#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int radius; int* shaderRGBA; int /*<<< orphan*/  customShader; int /*<<< orphan*/  origin; int /*<<< orphan*/  renderfx; int /*<<< orphan*/  reType; } ;
typedef  TYPE_4__ refEntity_t ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_10__ {int /*<<< orphan*/ * viewaxis; int /*<<< orphan*/  vieworg; } ;
struct TYPE_14__ {int damageValue; int time; int damageTime; int damageX; int damageY; TYPE_2__ refdef; } ;
struct TYPE_11__ {int /*<<< orphan*/  viewBloodShader; } ;
struct TYPE_9__ {scalar_t__ hardwareType; } ;
struct TYPE_13__ {TYPE_3__ media; TYPE_1__ glconfig; } ;

/* Variables and functions */
 int DAMAGE_TIME ; 
 scalar_t__ GLHW_RAGEPRO ; 
 int /*<<< orphan*/  RF_FIRST_PERSON ; 
 int /*<<< orphan*/  RT_SPRITE ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ cg ; 
 TYPE_7__ cgs ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_4__*) ; 

__attribute__((used)) static void CG_DamageBlendBlob( void ) {
	int			t;
	int			maxTime;
	refEntity_t		ent;

	if ( !cg.damageValue ) {
		return;
	}

	//if (cg.cameraMode) {
	//	return;
	//}

	// ragePro systems can't fade blends, so don't obscure the screen
	if ( cgs.glconfig.hardwareType == GLHW_RAGEPRO ) {
		return;
	}

	maxTime = DAMAGE_TIME;
	t = cg.time - cg.damageTime;
	if ( t <= 0 || t >= maxTime ) {
		return;
	}


	memset( &ent, 0, sizeof( ent ) );
	ent.reType = RT_SPRITE;
	ent.renderfx = RF_FIRST_PERSON;

	VectorMA( cg.refdef.vieworg, 8, cg.refdef.viewaxis[0], ent.origin );
	VectorMA( ent.origin, cg.damageX * -8, cg.refdef.viewaxis[1], ent.origin );
	VectorMA( ent.origin, cg.damageY * 8, cg.refdef.viewaxis[2], ent.origin );

	ent.radius = cg.damageValue * 3;
	ent.customShader = cgs.media.viewBloodShader;
	ent.shaderRGBA[0] = 255;
	ent.shaderRGBA[1] = 255;
	ent.shaderRGBA[2] = 255;
	ent.shaderRGBA[3] = 200 * ( 1.0 - ((float)t / maxTime) );
	trap_R_AddRefEntityToScene( &ent );
}