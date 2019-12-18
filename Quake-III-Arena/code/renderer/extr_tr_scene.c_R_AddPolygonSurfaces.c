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
struct TYPE_5__ {int /*<<< orphan*/  fogIndex; int /*<<< orphan*/  hShader; } ;
typedef  TYPE_2__ srfPoly_t ;
typedef  int /*<<< orphan*/  shader_t ;
struct TYPE_4__ {int numPolys; TYPE_2__* polys; } ;
struct TYPE_6__ {int currentEntityNum; int shiftedEntityNum; TYPE_1__ refdef; } ;

/* Variables and functions */
 int ENTITYNUM_WORLD ; 
 int QSORT_ENTITYNUM_SHIFT ; 
 int /*<<< orphan*/  R_AddDrawSurf (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * R_GetShaderByHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_3__ tr ; 

void R_AddPolygonSurfaces( void ) {
	int			i;
	shader_t	*sh;
	srfPoly_t	*poly;

	tr.currentEntityNum = ENTITYNUM_WORLD;
	tr.shiftedEntityNum = tr.currentEntityNum << QSORT_ENTITYNUM_SHIFT;

	for ( i = 0, poly = tr.refdef.polys; i < tr.refdef.numPolys ; i++, poly++ ) {
		sh = R_GetShaderByHandle( poly->hShader );
		R_AddDrawSurf( ( void * )poly, sh, poly->fogIndex, qfalse );
	}
}