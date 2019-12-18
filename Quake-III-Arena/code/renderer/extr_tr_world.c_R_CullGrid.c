#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  meshBounds; int /*<<< orphan*/  meshRadius; int /*<<< orphan*/  localOrigin; } ;
typedef  TYPE_2__ srfGridMesh_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_9__ {scalar_t__ integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  c_sphere_cull_patch_in; int /*<<< orphan*/  c_box_cull_patch_clip; int /*<<< orphan*/  c_box_cull_patch_in; int /*<<< orphan*/  c_box_cull_patch_out; int /*<<< orphan*/  c_sphere_cull_patch_clip; int /*<<< orphan*/  c_sphere_cull_patch_out; } ;
struct TYPE_8__ {scalar_t__ currentEntityNum; TYPE_1__ pc; } ;

/* Variables and functions */
 int CULL_CLIP ; 
 int CULL_IN ; 
 int CULL_OUT ; 
 scalar_t__ ENTITYNUM_WORLD ; 
 int R_CullLocalBox (int /*<<< orphan*/ ) ; 
 int R_CullLocalPointAndRadius (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int R_CullPointAndRadius (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_4__* r_nocurves ; 
 TYPE_3__ tr ; 

__attribute__((used)) static qboolean	R_CullGrid( srfGridMesh_t *cv ) {
	int 	boxCull;
	int 	sphereCull;

	if ( r_nocurves->integer ) {
		return qtrue;
	}

	if ( tr.currentEntityNum != ENTITYNUM_WORLD ) {
		sphereCull = R_CullLocalPointAndRadius( cv->localOrigin, cv->meshRadius );
	} else {
		sphereCull = R_CullPointAndRadius( cv->localOrigin, cv->meshRadius );
	}
	boxCull = CULL_OUT;
	
	// check for trivial reject
	if ( sphereCull == CULL_OUT )
	{
		tr.pc.c_sphere_cull_patch_out++;
		return qtrue;
	}
	// check bounding box if necessary
	else if ( sphereCull == CULL_CLIP )
	{
		tr.pc.c_sphere_cull_patch_clip++;

		boxCull = R_CullLocalBox( cv->meshBounds );

		if ( boxCull == CULL_OUT ) 
		{
			tr.pc.c_box_cull_patch_out++;
			return qtrue;
		}
		else if ( boxCull == CULL_IN )
		{
			tr.pc.c_box_cull_patch_in++;
		}
		else
		{
			tr.pc.c_box_cull_patch_clip++;
		}
	}
	else
	{
		tr.pc.c_sphere_cull_patch_in++;
	}

	return qfalse;
}