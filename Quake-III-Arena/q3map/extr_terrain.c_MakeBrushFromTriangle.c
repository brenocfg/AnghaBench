#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
typedef  int /*<<< orphan*/  shaderInfo_t ;
typedef  int /*<<< orphan*/  bspbrush_t ;
struct TYPE_4__ {int* portalareas; int /*<<< orphan*/  contents; int /*<<< orphan*/  brushnum; scalar_t__ entitynum; int /*<<< orphan*/  detail; scalar_t__ numsides; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddBrushSide (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONTENTS_DETAIL ; 
 int /*<<< orphan*/ * FinishBrush () ; 
 scalar_t__ MIN_WORLD_COORD ; 
 int /*<<< orphan*/  RemoveDuplicateBrushPlanes (TYPE_1__*) ; 
 int /*<<< orphan*/  SetBrushContents (TYPE_1__*) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* buildBrush ; 
 int /*<<< orphan*/  entitySourceBrushes ; 
 scalar_t__ num_entities ; 
 int /*<<< orphan*/  qfalse ; 

void MakeBrushFromTriangle( vec3_t v1, vec3_t v2, vec3_t v3, shaderInfo_t *terrainShader ) {
	bspbrush_t	*b;
	vec3_t		d1;
	vec3_t		d2;
	vec3_t		d3;

	VectorSet( d1, v1[ 0 ], v1[ 1 ], MIN_WORLD_COORD + 10 );	//FIXME
	VectorSet( d2, v2[ 0 ], v2[ 1 ], MIN_WORLD_COORD + 10 );
	VectorSet( d3, v3[ 0 ], v3[ 1 ], MIN_WORLD_COORD + 10 );

	buildBrush->numsides = 0;
	buildBrush->detail = qfalse;

	AddBrushSide( v1, v2, v3, terrainShader );
	AddBrushSide( v1, d1, v2, terrainShader );
	AddBrushSide( v2, d2, v3, terrainShader );
	AddBrushSide( v3, d3, v1, terrainShader );
	AddBrushSide( d3, d2, d1, terrainShader );

	buildBrush->portalareas[0] = -1;
	buildBrush->portalareas[1] = -1;
	buildBrush->entitynum = num_entities-1;
	buildBrush->brushnum = entitySourceBrushes;

	// if there are mirrored planes, the entire brush is invalid
	if ( !RemoveDuplicateBrushPlanes( buildBrush ) ) {
		return;
	}

	// get the content for the entire brush
	SetBrushContents( buildBrush );
	buildBrush->contents |= CONTENTS_DETAIL;

	b = FinishBrush();
	if ( !b ) {
		return;
	}
}