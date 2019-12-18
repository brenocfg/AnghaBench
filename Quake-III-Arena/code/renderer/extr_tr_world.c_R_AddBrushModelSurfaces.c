#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  hModel; } ;
struct TYPE_12__ {TYPE_2__ e; } ;
typedef  TYPE_3__ trRefEntity_t ;
struct TYPE_13__ {TYPE_5__* bmodel; } ;
typedef  TYPE_4__ model_t ;
struct TYPE_14__ {int numSurfaces; scalar_t__ firstSurface; int /*<<< orphan*/  bounds; } ;
typedef  TYPE_5__ bmodel_t ;
struct TYPE_15__ {TYPE_1__* currentEntity; } ;
struct TYPE_10__ {int /*<<< orphan*/  needDlights; } ;

/* Variables and functions */
 int CULL_OUT ; 
 int /*<<< orphan*/  R_AddWorldSurface (scalar_t__,int /*<<< orphan*/ ) ; 
 int R_CullLocalBox (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_DlightBmodel (TYPE_5__*) ; 
 TYPE_4__* R_GetModelByHandle (int /*<<< orphan*/ ) ; 
 TYPE_6__ tr ; 

void R_AddBrushModelSurfaces ( trRefEntity_t *ent ) {
	bmodel_t	*bmodel;
	int			clip;
	model_t		*pModel;
	int			i;

	pModel = R_GetModelByHandle( ent->e.hModel );

	bmodel = pModel->bmodel;

	clip = R_CullLocalBox( bmodel->bounds );
	if ( clip == CULL_OUT ) {
		return;
	}
	
	R_DlightBmodel( bmodel );

	for ( i = 0 ; i < bmodel->numSurfaces ; i++ ) {
		R_AddWorldSurface( bmodel->firstSurface + i, tr.currentEntity->needDlights );
	}
}