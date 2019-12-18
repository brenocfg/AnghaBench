#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int surfaceFlags; } ;
typedef  TYPE_2__ shaderInfo_t ;
struct TYPE_12__ {int lightmapNum; struct TYPE_12__* nextOnShader; TYPE_2__* shaderInfo; int /*<<< orphan*/ * lightmapVecs; TYPE_1__* side; int /*<<< orphan*/  patch; scalar_t__ miscModel; int /*<<< orphan*/  numVerts; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_13__ {int firstDrawSurf; } ;
typedef  TYPE_4__ entity_t ;
struct TYPE_14__ {int /*<<< orphan*/  normal; } ;
struct TYPE_10__ {size_t planenum; } ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateLightmapForSurface (TYPE_3__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int LIGHTMAP_HEIGHT ; 
 int LIGHTMAP_WIDTH ; 
 int MAX_MAP_SHADERS ; 
 int SURF_NOLIGHTMAP ; 
 int SURF_POINTLIGHT ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int c_exactLightmap ; 
 TYPE_3__* mapDrawSurfs ; 
 TYPE_6__* mapplanes ; 
 int numLightmaps ; 
 int numMapDrawSurfs ; 
 int numSortShaders ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 TYPE_3__** surfsOnShader ; 

void AllocateLightmaps( entity_t *e ) {
	int				i, j;
	mapDrawSurface_t	*ds;
	shaderInfo_t	*si;

	qprintf ("--- AllocateLightmaps ---\n");


	// sort all surfaces by shader so common shaders will usually
	// be in the same lightmap
	numSortShaders = 0;

	for ( i = e->firstDrawSurf ; i < numMapDrawSurfs ; i++ ) {
		ds = &mapDrawSurfs[i];
		if ( !ds->numVerts ) {
			continue;		// leftover from a surface subdivision
		}
		if ( ds->miscModel ) {
			continue;
		}
		if ( !ds->patch ) {
			VectorCopy( mapplanes[ds->side->planenum].normal, ds->lightmapVecs[2] );
		}

		// search for this shader
		for ( j = 0 ; j < numSortShaders ; j++ ) {
			if ( ds->shaderInfo == surfsOnShader[j]->shaderInfo ) {
				ds->nextOnShader = surfsOnShader[j];
				surfsOnShader[j] = ds;
				break;
			}
		}
		if ( j == numSortShaders ) {
			if ( numSortShaders >= MAX_MAP_SHADERS ) {
				Error( "MAX_MAP_SHADERS" );
			}
			surfsOnShader[j] = ds;
			numSortShaders++;
		}
	}
	qprintf( "%5i unique shaders\n", numSortShaders );

	// for each shader, allocate lightmaps for each surface

//	numLightmaps = 0;
//	PrepareNewLightmap();

	for ( i = 0 ; i < numSortShaders ; i++ ) {
		si = surfsOnShader[i]->shaderInfo;

		for ( ds = surfsOnShader[i] ; ds ; ds = ds->nextOnShader ) {
			// some surfaces don't need lightmaps allocated for them
			if ( si->surfaceFlags & SURF_NOLIGHTMAP ) {
				ds->lightmapNum = -1;
			} else if ( si->surfaceFlags & SURF_POINTLIGHT ) {
				ds->lightmapNum = -3;
			} else {
				AllocateLightmapForSurface( ds );
			}
		}
	}

	qprintf( "%7i exact lightmap texels\n", c_exactLightmap );
	qprintf( "%7i block lightmap texels\n", numLightmaps * LIGHTMAP_WIDTH*LIGHTMAP_HEIGHT );
}