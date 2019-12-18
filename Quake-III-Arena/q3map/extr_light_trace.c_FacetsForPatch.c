#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int numFacets; int /*<<< orphan*/ * facets; int /*<<< orphan*/ * shader; int /*<<< orphan*/  patch; } ;
typedef  TYPE_1__ surfaceTest_t ;
typedef  int /*<<< orphan*/  shaderInfo_t ;
struct TYPE_14__ {int width; int height; int /*<<< orphan*/ * verts; } ;
typedef  TYPE_2__ mesh_t ;
struct TYPE_15__ {int patchWidth; int patchHeight; size_t firstVert; } ;
typedef  TYPE_3__ dsurface_t ;
typedef  int /*<<< orphan*/  drawVert_t ;

/* Variables and functions */
 scalar_t__ CM_GenerateFacetFor3Points (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CM_GenerateFacetFor4Points (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeMesh (TYPE_2__*) ; 
 int /*<<< orphan*/  MakeMeshNormals (TYPE_2__) ; 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_2__) ; 
 TYPE_2__* RemoveLinearMeshColumnsRows (TYPE_2__*) ; 
 TYPE_2__* SubdivideMesh (TYPE_2__,int,int) ; 
 int /*<<< orphan*/ * drawVerts ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  qtrue ; 

void FacetsForPatch( dsurface_t *dsurf, shaderInfo_t *si, surfaceTest_t *test ) {
	int			i, j;
	drawVert_t	*v1, *v2, *v3, *v4;
	int			count;
	mesh_t		srcMesh, *subdivided, *mesh;

	srcMesh.width = dsurf->patchWidth;
	srcMesh.height = dsurf->patchHeight;
	srcMesh.verts = &drawVerts[ dsurf->firstVert ];

	//subdivided = SubdivideMesh( mesh, CURVE_FACET_ERROR, 9999 );
	mesh = SubdivideMesh( srcMesh, 8, 999 );
	PutMeshOnCurve( *mesh );
	MakeMeshNormals( *mesh );

	subdivided = RemoveLinearMeshColumnsRows( mesh );
	FreeMesh(mesh);

	test->patch = qtrue;
	test->numFacets = ( subdivided->width - 1 ) * ( subdivided->height - 1 ) * 2;
	test->facets = malloc( sizeof( test->facets[0] ) * test->numFacets );
	test->shader = si;

	count = 0;
	for ( i = 0 ; i < subdivided->width - 1 ; i++ ) {
		for ( j = 0 ; j < subdivided->height - 1 ; j++ ) {

			v1 = subdivided->verts + j * subdivided->width + i;
			v2 = v1 + 1;
			v3 = v1 + subdivided->width + 1;
			v4 = v1 + subdivided->width;

			if ( CM_GenerateFacetFor4Points( &test->facets[count], v1, v4, v3, v2 ) ) {
				count++;
			} else {
				if (CM_GenerateFacetFor3Points( &test->facets[count], v1, v4, v3 ))
					count++;
				if (CM_GenerateFacetFor3Points( &test->facets[count], v1, v3, v2 ))
					count++;
			}
		}
	}
	test->numFacets = count;
	FreeMesh(subdivided);
}