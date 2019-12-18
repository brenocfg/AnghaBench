#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_12__ {float* start; float* end; TYPE_1__* trace; } ;
typedef  TYPE_2__ traceWork_t ;
struct TYPE_13__ {int surfaceFlags; } ;
typedef  TYPE_3__ shaderInfo_t ;
struct TYPE_14__ {int numBoundaries; float* surface; float** boundaries; } ;
typedef  TYPE_4__ cFacet_t ;
struct TYPE_11__ {float hitFraction; int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 float DotProduct (float*,float*) ; 
 float ON_EPSILON ; 
 int SURF_ALPHASHADOW ; 
 int /*<<< orphan*/  SetFacetFilter (TYPE_2__*,TYPE_3__*,TYPE_4__*,float*) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 

void TraceAgainstFacet( traceWork_t *tr, shaderInfo_t *shader, cFacet_t *facet ) {
	int			j;
	float		d1, d2, d, f;
	vec3_t		point;
	float		dist;

	// ignore degenerate facets
	if ( facet->numBoundaries < 3 ) {
		return;
	}

	dist = facet->surface[3];

	// compare the trace endpoints against the facet plane
	d1 = DotProduct( tr->start, facet->surface ) - dist;
	if ( d1 > -1 && d1 < 1 ) {
		return;		// don't self intersect
	}
	d2 = DotProduct( tr->end, facet->surface ) - dist;
	if ( d2 > -1 && d2 < 1 ) {
		return;		// don't self intersect
	}

	// calculate the intersection fraction
	f = ( d1 - ON_EPSILON ) / ( d1 - d2 );
	if ( f <= 0 ) {
		return;
	}
	if ( f >= tr->trace->hitFraction ) {
		return;			// we have hit something earlier
	}

	// calculate the intersection point
	for ( j = 0 ; j < 3 ; j++ ) {
		point[j] = tr->start[j] + f * ( tr->end[j] - tr->start[j] );
	}

	// check the point against the facet boundaries
	for ( j = 0 ; j < facet->numBoundaries ; j++ ) {
		// adjust the plane distance apropriately for mins/maxs
		dist = facet->boundaries[j][3];

		d = DotProduct( point, facet->boundaries[j] );
		if ( d > dist + ON_EPSILON ) {
			break;		// outside the bounds
		}
	}

	if ( j != facet->numBoundaries ) {
		return;			// we are outside the bounds of the facet
	}

	// we hit this facet

	// if this is a transparent surface, calculate filter value
	if ( shader->surfaceFlags & SURF_ALPHASHADOW ) {
		SetFacetFilter( tr, shader, facet, point );
	} else {
		// completely opaque
		VectorClear( tr->trace->filter );
		tr->trace->hitFraction = f;
	}

//	VectorCopy( facet->surface, tr->trace->plane.normal );
//	tr->trace->plane.dist = facet->surface[3];
}