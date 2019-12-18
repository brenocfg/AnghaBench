#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  float* vec3_t ;
struct TYPE_11__ {int /*<<< orphan*/  fogNum; int /*<<< orphan*/  side; int /*<<< orphan*/  mapBrush; } ;
typedef  TYPE_2__ mapDrawSurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,float*,float*) ; 
 int /*<<< orphan*/  ClearBounds (float*,float*) ; 
 int /*<<< orphan*/  ClipWindingEpsilon (TYPE_1__*,float*,float,float const,TYPE_1__**,TYPE_1__**) ; 
 float DotProduct (float*,float*) ; 
 TYPE_2__* DrawSurfaceForSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 float ceil (float) ; 
 float floor (float) ; 

void SubdivideDrawSurf( mapDrawSurface_t *ds, winding_t *w, float subdivisions ) {
	int				i;
	int				axis;
	vec3_t			bounds[2];
	const float		epsilon = 0.1;
	int				subFloor, subCeil;
	winding_t		*frontWinding, *backWinding;
	mapDrawSurface_t	*newds;

	if ( !w ) {
		return;
	}
	if ( w->numpoints < 3 ) {
		Error( "SubdivideDrawSurf: Bad w->numpoints" );
	}

	ClearBounds( bounds[0], bounds[1] );
	for ( i = 0 ; i < w->numpoints ; i++ ) {
		AddPointToBounds( w->p[i], bounds[0], bounds[1] );
	}

	for ( axis = 0 ; axis < 3 ; axis++ ) {
		vec3_t planePoint = { 0, 0, 0 };
		vec3_t planeNormal = { 0, 0, 0 };
		float d;

		subFloor = floor( bounds[0][axis]  / subdivisions ) * subdivisions;
		subCeil = ceil( bounds[1][axis] / subdivisions ) * subdivisions;

		planePoint[axis] = subFloor + subdivisions;
		planeNormal[axis] = -1;

		d = DotProduct( planePoint, planeNormal );

		// subdivide if necessary
		if ( subCeil - subFloor > subdivisions ) {
			// gotta clip polygon into two polygons
			ClipWindingEpsilon( w, planeNormal, d, epsilon, &frontWinding, &backWinding );

			// the clip may not produce two polygons if it was epsilon close
			if ( !frontWinding ) {
				w = backWinding;
			} else if ( !backWinding ) {
				w = frontWinding;
			} else {
				SubdivideDrawSurf( ds, frontWinding, subdivisions );
				SubdivideDrawSurf( ds, backWinding, subdivisions );

				return;
			}
		}
	}

	// emit this polygon
	newds = DrawSurfaceForSide( ds->mapBrush, ds->side, w );
	newds->fogNum = ds->fogNum;
}