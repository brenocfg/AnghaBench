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
struct TYPE_4__ {int numVerts; int numIndexes; scalar_t__ firstIndex; scalar_t__ firstVert; } ;
typedef  TYPE_1__ dsurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ IsTriangleDegenerate (scalar_t__,int,int,int) ; 
 int MAX_INDICES ; 
 scalar_t__ MAX_MAP_DRAW_INDEXES ; 
 int /*<<< orphan*/  SurfaceAsTriFan (TYPE_1__*) ; 
 int /*<<< orphan*/  c_fanSurfaces ; 
 int /*<<< orphan*/  c_stripSurfaces ; 
 scalar_t__ drawIndexes ; 
 scalar_t__ drawVerts ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 
 scalar_t__ numDrawIndexes ; 

__attribute__((used)) static void SurfaceAsTristrip( dsurface_t *ds ) {
	int					i;
	int					rotate;
	int					numIndices;
	int					ni;
	int					a, b, c;
	int					indices[MAX_INDICES];

	// determine the triangle strip order
	numIndices = ( ds->numVerts - 2 ) * 3;
	if ( numIndices > MAX_INDICES ) {
		Error( "MAX_INDICES exceeded for surface" );
	}

	// try all possible orderings of the points looking
	// for a strip order that isn't degenerate
	for ( rotate = 0 ; rotate < ds->numVerts ; rotate++ ) {
		for ( ni = 0, i = 0 ; i < ds->numVerts - 2 - i ; i++ ) {
			a = ( ds->numVerts - 1 - i + rotate ) % ds->numVerts;
			b = ( i + rotate ) % ds->numVerts;
			c = ( ds->numVerts - 2 - i + rotate ) % ds->numVerts;

			if ( IsTriangleDegenerate( drawVerts + ds->firstVert, a, b, c ) ) {
				break;
			}
			indices[ni++] = a;
			indices[ni++] = b;
			indices[ni++] = c;

			if ( i + 1 != ds->numVerts - 1 - i ) {
				a = ( ds->numVerts - 2 - i + rotate ) % ds->numVerts;
				b = ( i + rotate ) % ds->numVerts;
				c = ( i + 1 + rotate ) % ds->numVerts;

				if ( IsTriangleDegenerate( drawVerts + ds->firstVert, a, b, c ) ) {
					break;
				}
				indices[ni++] = a;
				indices[ni++] = b;
				indices[ni++] = c;
			}
		}
		if ( ni == numIndices ) {
			break;		// got it done without degenerate triangles
		}
	}

	// if any triangle in the strip is degenerate,
	// render from a centered fan point instead
	if ( ni < numIndices ) {
		c_fanSurfaces++;
		SurfaceAsTriFan( ds );
		return;
	}

	// a normal tristrip
	c_stripSurfaces++;

	if ( numDrawIndexes + ni > MAX_MAP_DRAW_INDEXES ) {
		Error( "MAX_MAP_DRAW_INDEXES" );
	}
	ds->firstIndex = numDrawIndexes;
	ds->numIndexes = ni;

	memcpy( drawIndexes + numDrawIndexes, indices, ni * sizeof(int) );
	numDrawIndexes += ni;
}