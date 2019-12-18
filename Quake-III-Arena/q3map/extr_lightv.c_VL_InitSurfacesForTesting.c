#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int contents; int surfaceFlags; scalar_t__ forceVLight; scalar_t__ forceTraceLight; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_18__ {int numFacets; int /*<<< orphan*/  radius; int /*<<< orphan*/  origin; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; TYPE_3__* facets; void* always_vlight; void* always_tracelight; scalar_t__ numvolumes; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ lsurfaceTest_t ;
struct TYPE_19__ {int numpoints; int /*<<< orphan*/ * points; } ;
typedef  TYPE_3__ lFacet_t ;
struct TYPE_20__ {size_t shaderNum; scalar_t__ lightmapNum; scalar_t__ surfaceType; int /*<<< orphan*/  patchWidth; int /*<<< orphan*/  numIndexes; } ;
typedef  TYPE_4__ dsurface_t ;
struct TYPE_21__ {int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CONTENTS_TRANSLUCENT ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*,scalar_t__) ; 
 scalar_t__ MAX_FACETS ; 
 scalar_t__ MST_PATCH ; 
 scalar_t__ MST_PLANAR ; 
 scalar_t__ MST_TRIANGLE_SOUP ; 
 int /*<<< orphan*/  MutexAlloc () ; 
 int SURF_ALPHASHADOW ; 
 TYPE_1__* ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VL_FacetsForPatch (TYPE_4__*,int,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  VL_FacetsForTriangleSurface (TYPE_4__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  VL_LinkSurfaces () ; 
 int /*<<< orphan*/  VL_SphereFromBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _printf (char*,...) ; 
 TYPE_4__* drawSurfaces ; 
 TYPE_8__* dshaders ; 
 scalar_t__* entitySurface ; 
 TYPE_2__** lsurfaceTest ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int numDrawSurfaces ; 
 scalar_t__ numfacets ; 
 void* qtrue ; 

void VL_InitSurfacesForTesting( void ) {

	int				i, j, k;
	dsurface_t		*dsurf;
	lsurfaceTest_t	*test;
	shaderInfo_t	*si;
	lFacet_t		*facet;

	for ( i = 0 ; i < numDrawSurfaces ; i++ ) {
		// don't light the entity surfaces with vlight
		if ( entitySurface[i] )
			continue;
		//
		dsurf = &drawSurfaces[ i ];
		if ( !dsurf->numIndexes && !dsurf->patchWidth ) {
			continue;
		}

		si = ShaderInfoForShader( dshaders[ dsurf->shaderNum].shader );
		// if the surface is translucent and does not cast an alpha shadow
		if ( (si->contents & CONTENTS_TRANSLUCENT) && !(si->surfaceFlags & SURF_ALPHASHADOW) ) {
			// if the surface has no lightmap
			if ( dsurf->lightmapNum < 0 )
				continue;
		}

		test = malloc( sizeof( *test ) );
		memset(test, 0, sizeof( *test ));
		test->mutex = MutexAlloc();
		test->numvolumes = 0;
		if (si->forceTraceLight)
			test->always_tracelight = qtrue;
		else if (si->forceVLight)
			test->always_vlight = qtrue;
		lsurfaceTest[i] = test;

		if ( dsurf->surfaceType == MST_TRIANGLE_SOUP || dsurf->surfaceType == MST_PLANAR ) {
			VL_FacetsForTriangleSurface( dsurf, si, test );
		} else if ( dsurf->surfaceType == MST_PATCH ) {
			VL_FacetsForPatch( dsurf, i, si, test );
		}
		if (numfacets >= MAX_FACETS)
			Error("numfacets >= MAX_FACETS (%d)", MAX_FACETS);

		ClearBounds( test->mins, test->maxs );
		for (j = 0; j < test->numFacets; j++)
		{
			facet = &test->facets[j];
			for ( k = 0 ; k < facet->numpoints; k++) {
				AddPointToBounds( facet->points[k], test->mins, test->maxs );
			}
		}
		VL_SphereFromBounds( test->mins, test->maxs, test->origin, &test->radius );
	}
	_printf("%6d facets\n", numfacets);
	_printf("linking surfaces...\n");
	VL_LinkSurfaces();
}