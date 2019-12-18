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
struct TYPE_5__ {int firstVert; int numVerts; int numIndexes; scalar_t__ firstIndex; } ;
typedef  TYPE_1__ dsurface_t ;
struct TYPE_6__ {int* xyz; int* st; int* lightmap; int* color; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ drawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ MAX_MAP_DRAW_INDEXES ; 
 size_t MAX_MAP_DRAW_VERTS ; 
 int /*<<< orphan*/  VectorAdd (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* drawIndexes ; 
 TYPE_2__* drawVerts ; 
 scalar_t__ numDrawIndexes ; 
 size_t numDrawVerts ; 

__attribute__((used)) static void SurfaceAsTriFan( dsurface_t *ds ) {
	int					i;
	int					colorSum[4];
	drawVert_t			*mid, *v;

	// create a new point in the center of the face
	if ( numDrawVerts == MAX_MAP_DRAW_VERTS ) {
		Error( "MAX_MAP_DRAW_VERTS" );
	}
	mid = &drawVerts[ numDrawVerts ];
	numDrawVerts++;

	colorSum[0] = colorSum[1] = colorSum[2] = colorSum[3] = 0;

	v = drawVerts + ds->firstVert;
	for (i = 0 ; i < ds->numVerts ; i++, v++ ) {
		VectorAdd( mid->xyz, v->xyz, mid->xyz );
		mid->st[0] += v->st[0];
		mid->st[1] += v->st[1];
		mid->lightmap[0] += v->lightmap[0];
		mid->lightmap[1] += v->lightmap[1];

		colorSum[0] += v->color[0];
		colorSum[1] += v->color[1];
		colorSum[2] += v->color[2];
		colorSum[3] += v->color[3];
	}

	mid->xyz[0] /= ds->numVerts;
	mid->xyz[1] /= ds->numVerts;
	mid->xyz[2] /= ds->numVerts;

	mid->st[0] /= ds->numVerts;
	mid->st[1] /= ds->numVerts;

	mid->lightmap[0] /= ds->numVerts;
	mid->lightmap[1] /= ds->numVerts;

	mid->color[0] = colorSum[0] / ds->numVerts;
	mid->color[1] = colorSum[1] / ds->numVerts;
	mid->color[2] = colorSum[2] / ds->numVerts;
	mid->color[3] = colorSum[3] / ds->numVerts;

	VectorCopy((drawVerts+ds->firstVert)->normal, mid->normal );

	// fill in indices in trifan order
	if ( numDrawIndexes + ds->numVerts*3 > MAX_MAP_DRAW_INDEXES ) {
		Error( "MAX_MAP_DRAWINDEXES" );
	}
	ds->firstIndex = numDrawIndexes;
	ds->numIndexes = ds->numVerts*3;

	//FIXME
	// should be: for ( i = 0 ; i < ds->numVerts ; i++ ) {
	// set a break point and test this in a map
	//for ( i = 0 ; i < ds->numVerts*3 ; i++ ) {
	for ( i = 0 ; i < ds->numVerts ; i++ ) {
		drawIndexes[numDrawIndexes++] = ds->numVerts;
		drawIndexes[numDrawIndexes++] = i;
		drawIndexes[numDrawIndexes++] = (i+1) % ds->numVerts;
	}

	ds->numVerts++;
}