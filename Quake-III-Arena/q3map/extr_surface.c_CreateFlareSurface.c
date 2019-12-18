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
struct TYPE_8__ {int numVerts; int /*<<< orphan*/ * lightmapVecs; TYPE_2__* shaderInfo; int /*<<< orphan*/  lightmapOrigin; TYPE_1__* verts; int /*<<< orphan*/  flareSurface; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_7__ {char* flareShader; int /*<<< orphan*/  color; } ;
struct TYPE_6__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 TYPE_3__* AllocDrawSurf () ; 
 void* ShaderInfoForShader (char*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 

void CreateFlareSurface( mapDrawSurface_t *faceDs ) {
	mapDrawSurface_t	*ds;
	int					i;

	ds = AllocDrawSurf();

	if ( faceDs->shaderInfo->flareShader[0] ) {
		ds->shaderInfo = ShaderInfoForShader( faceDs->shaderInfo->flareShader );
	} else {
		ds->shaderInfo = ShaderInfoForShader( "flareshader" );
	}
	ds->flareSurface = qtrue;
	VectorCopy( faceDs->lightmapVecs[2], ds->lightmapVecs[2] );

	// find midpoint
	VectorClear( ds->lightmapOrigin );
	for ( i = 0 ; i < faceDs->numVerts ; i++ ) {
		VectorAdd( ds->lightmapOrigin, faceDs->verts[i].xyz, ds->lightmapOrigin );
	}
	VectorScale( ds->lightmapOrigin, 1.0/faceDs->numVerts, ds->lightmapOrigin );

	VectorMA( ds->lightmapOrigin, 2,  ds->lightmapVecs[2], ds->lightmapOrigin );

	VectorCopy( faceDs->shaderInfo->color, ds->lightmapVecs[0] );

	// FIXME: fog
}