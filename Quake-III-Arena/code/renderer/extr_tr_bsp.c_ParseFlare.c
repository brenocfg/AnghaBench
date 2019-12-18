#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  surfaceType_t ;
struct TYPE_11__ {void** normal; void** color; void** origin; int /*<<< orphan*/  surfaceType; } ;
typedef  TYPE_1__ srfFlare_t ;
struct TYPE_12__ {int /*<<< orphan*/ * data; TYPE_8__* shader; scalar_t__ fogIndex; } ;
typedef  TYPE_2__ msurface_t ;
struct TYPE_13__ {int /*<<< orphan*/ ** lightmapVecs; int /*<<< orphan*/ * lightmapOrigin; int /*<<< orphan*/  shaderNum; int /*<<< orphan*/  fogNum; } ;
typedef  TYPE_3__ dsurface_t ;
typedef  int /*<<< orphan*/  drawVert_t ;
struct TYPE_17__ {int /*<<< orphan*/  isSky; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {TYPE_1__* (* Hunk_Alloc ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {TYPE_8__* defaultShader; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIGHTMAP_BY_VERTEX ; 
 void* LittleFloat (int /*<<< orphan*/ ) ; 
 scalar_t__ LittleLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SF_FLARE ; 
 TYPE_8__* ShaderForShaderNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_low ; 
 TYPE_7__* r_singleShader ; 
 TYPE_6__ ri ; 
 TYPE_1__* stub1 (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ tr ; 

__attribute__((used)) static void ParseFlare( dsurface_t *ds, drawVert_t *verts, msurface_t *surf, int *indexes ) {
	srfFlare_t		*flare;
	int				i;

	// get fog volume
	surf->fogIndex = LittleLong( ds->fogNum ) + 1;

	// get shader
	surf->shader = ShaderForShaderNum( ds->shaderNum, LIGHTMAP_BY_VERTEX );
	if ( r_singleShader->integer && !surf->shader->isSky ) {
		surf->shader = tr.defaultShader;
	}

	flare = ri.Hunk_Alloc( sizeof( *flare ), h_low );
	flare->surfaceType = SF_FLARE;

	surf->data = (surfaceType_t *)flare;

	for ( i = 0 ; i < 3 ; i++ ) {
		flare->origin[i] = LittleFloat( ds->lightmapOrigin[i] );
		flare->color[i] = LittleFloat( ds->lightmapVecs[0][i] );
		flare->normal[i] = LittleFloat( ds->lightmapVecs[2][i] );
	}
}