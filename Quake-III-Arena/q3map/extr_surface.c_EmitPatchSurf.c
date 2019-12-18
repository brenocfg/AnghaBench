#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numVerts; int numIndexes; int /*<<< orphan*/ * indexes; int /*<<< orphan*/ * verts; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; int /*<<< orphan*/  lightmapHeight; int /*<<< orphan*/  lightmapWidth; int /*<<< orphan*/  lightmapY; int /*<<< orphan*/  lightmapX; int /*<<< orphan*/  lightmapNum; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  patchHeight; int /*<<< orphan*/  patchWidth; TYPE_1__* shaderInfo; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_11__ {size_t firstVert; int numVerts; size_t firstIndex; int numIndexes; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; int /*<<< orphan*/  lightmapHeight; int /*<<< orphan*/  lightmapWidth; int /*<<< orphan*/  lightmapY; int /*<<< orphan*/  lightmapX; int /*<<< orphan*/  lightmapNum; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  patchHeight; int /*<<< orphan*/  patchWidth; int /*<<< orphan*/  shaderNum; int /*<<< orphan*/  surfaceType; } ;
typedef  TYPE_3__ dsurface_t ;
struct TYPE_12__ {int* color; } ;
typedef  TYPE_4__ drawVert_t ;
struct TYPE_9__ {int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmitShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_DRAW_INDEXES ; 
 size_t MAX_MAP_DRAW_SURFS ; 
 size_t MAX_MAP_DRAW_VERTS ; 
 int /*<<< orphan*/  MST_PATCH ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * drawIndexes ; 
 TYPE_3__* drawSurfaces ; 
 TYPE_4__* drawVerts ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 size_t numDrawIndexes ; 
 size_t numDrawSurfaces ; 
 size_t numDrawVerts ; 

void EmitPatchSurf( mapDrawSurface_t *ds ) {
	int				j;
	dsurface_t		*out;
	drawVert_t		*outv;

	if ( numDrawSurfaces == MAX_MAP_DRAW_SURFS ) {
		Error( "MAX_MAP_DRAW_SURFS" );
	}
	out = &drawSurfaces[ numDrawSurfaces ];
	numDrawSurfaces++;

	out->surfaceType = MST_PATCH;
	out->shaderNum = EmitShader( ds->shaderInfo->shader );
	out->firstVert = numDrawVerts;
	out->numVerts = ds->numVerts;
	out->firstIndex = numDrawIndexes;
	out->numIndexes = ds->numIndexes;
	out->patchWidth = ds->patchWidth;
	out->patchHeight = ds->patchHeight;
	out->fogNum = ds->fogNum;
	out->lightmapNum = ds->lightmapNum;
	out->lightmapX = ds->lightmapX;
	out->lightmapY = ds->lightmapY;
	out->lightmapWidth = ds->lightmapWidth;
	out->lightmapHeight = ds->lightmapHeight;

	VectorCopy( ds->lightmapOrigin, out->lightmapOrigin );
	VectorCopy( ds->lightmapVecs[0], out->lightmapVecs[0] );
	VectorCopy( ds->lightmapVecs[1], out->lightmapVecs[1] );
	VectorCopy( ds->lightmapVecs[2], out->lightmapVecs[2] );

	for ( j = 0 ; j < ds->numVerts ; j++ ) {
		if ( numDrawVerts == MAX_MAP_DRAW_VERTS ) {
			Error( "MAX_MAP_DRAW_VERTS" );
		}
		outv = &drawVerts[ numDrawVerts ];
		numDrawVerts++;
		memcpy( outv, &ds->verts[ j ], sizeof( *outv ) );
		outv->color[0] = 255;
		outv->color[1] = 255;
		outv->color[2] = 255;
		outv->color[3] = 255;
	}

	for ( j = 0 ; j < ds->numIndexes ; j++ ) {
		if ( numDrawIndexes == MAX_MAP_DRAW_INDEXES ) {
			Error( "MAX_MAP_DRAW_INDEXES" );
		}
		drawIndexes[ numDrawIndexes ] = ds->indexes[ j ];
		numDrawIndexes++;
	}
}