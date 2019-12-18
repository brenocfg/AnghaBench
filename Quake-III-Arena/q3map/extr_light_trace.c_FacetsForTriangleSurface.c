#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numFacets; int /*<<< orphan*/ * facets; int /*<<< orphan*/ * shader; int /*<<< orphan*/  patch; } ;
typedef  TYPE_1__ surfaceTest_t ;
typedef  int /*<<< orphan*/  shaderInfo_t ;
struct TYPE_6__ {int numIndexes; int firstIndex; int firstVert; } ;
typedef  TYPE_2__ dsurface_t ;
typedef  int /*<<< orphan*/  drawVert_t ;

/* Variables and functions */
 scalar_t__ CM_GenerateFacetFor3Points (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CM_GenerateFacetFor4Points (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* drawIndexes ; 
 int /*<<< orphan*/ * drawVerts ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  qfalse ; 

void FacetsForTriangleSurface( dsurface_t *dsurf, shaderInfo_t *si, surfaceTest_t *test ) {
	int			i;
	drawVert_t	*v1, *v2, *v3, *v4;
	int			count;
	int			i1, i2, i3, i4, i5, i6;

	test->patch = qfalse;
	test->numFacets = dsurf->numIndexes / 3;
	test->facets = malloc( sizeof( test->facets[0] ) * test->numFacets );
	test->shader = si;

	count = 0;
	for ( i = 0 ; i < test->numFacets ; i++ ) {
		i1 = drawIndexes[ dsurf->firstIndex + i*3 ];
		i2 = drawIndexes[ dsurf->firstIndex + i*3 + 1 ];
		i3 = drawIndexes[ dsurf->firstIndex + i*3 + 2 ];

		v1 = &drawVerts[ dsurf->firstVert + i1 ];
		v2 = &drawVerts[ dsurf->firstVert + i2 ];
		v3 = &drawVerts[ dsurf->firstVert + i3 ];

		// try and make a quad out of two triangles
		if ( i != test->numFacets - 1 ) {
			i4 = drawIndexes[ dsurf->firstIndex + i*3 + 3 ];
			i5 = drawIndexes[ dsurf->firstIndex + i*3 + 4 ];
			i6 = drawIndexes[ dsurf->firstIndex + i*3 + 5 ];
			if ( i4 == i3 && i5 == i2 ) {
				v4 = &drawVerts[ dsurf->firstVert + i6 ];
				if ( CM_GenerateFacetFor4Points( &test->facets[count], v1, v2, v4, v3 ) ) {
					count++;
					i++;		// skip next tri
					continue;
				}
			}
		}

		if (CM_GenerateFacetFor3Points( &test->facets[count], v1, v2, v3 ))
			count++;
	}		

	// we may have turned some pairs into quads
	test->numFacets = count;
}