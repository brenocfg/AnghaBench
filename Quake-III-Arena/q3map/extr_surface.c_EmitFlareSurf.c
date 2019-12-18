#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; int /*<<< orphan*/  fogNum; TYPE_1__* shaderInfo; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_8__ {int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  shaderNum; int /*<<< orphan*/  surfaceType; } ;
typedef  TYPE_3__ dsurface_t ;
struct TYPE_6__ {int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmitShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_DRAW_SURFS ; 
 int /*<<< orphan*/  MST_FLARE ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* drawSurfaces ; 
 size_t numDrawSurfaces ; 

void EmitFlareSurf( mapDrawSurface_t *ds ) {
	dsurface_t		*out;

	if ( numDrawSurfaces == MAX_MAP_DRAW_SURFS ) {
		Error( "MAX_MAP_DRAW_SURFS" );
	}
	out = &drawSurfaces[ numDrawSurfaces ];
	numDrawSurfaces++;

	out->surfaceType = MST_FLARE;
	out->shaderNum = EmitShader( ds->shaderInfo->shader );
	out->fogNum = ds->fogNum;

	VectorCopy( ds->lightmapOrigin, out->lightmapOrigin );
	VectorCopy( ds->lightmapVecs[0], out->lightmapVecs[0] );	// color
	VectorCopy( ds->lightmapVecs[2], out->lightmapVecs[2] );
}