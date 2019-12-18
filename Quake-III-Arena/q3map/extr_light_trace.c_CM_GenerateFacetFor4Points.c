#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_12__ {float* xyz; } ;
typedef  TYPE_1__ drawVert_t ;
struct TYPE_13__ {float* surface; int numBoundaries; float** points; int /*<<< orphan*/ * boundaries; } ;
typedef  TYPE_2__ cFacet_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_GenerateBoundaryForPoints (int /*<<< orphan*/ ,float*,float*,float*) ; 
 double DotProduct (float*,float*) ; 
 scalar_t__ PLANAR_EPSILON ; 
 int /*<<< orphan*/  PlaneFromPoints (float*,float*,float*,float*) ; 
 int /*<<< orphan*/  TextureMatrixFromPoints (TYPE_2__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 scalar_t__ fabs (float) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean CM_GenerateFacetFor4Points( cFacet_t *f, drawVert_t *a, drawVert_t *b, drawVert_t *c, drawVert_t *d ) {
	float	dist;
	int		i;
	vec4_t	plane;

	// if we can't generate a valid plane for the points, ignore the facet
	if ( !PlaneFromPoints( f->surface, a->xyz, b->xyz, c->xyz ) ) {
		f->numBoundaries = 0;
		return qfalse;
	}

	// if the fourth point is also on the plane, we can make a quad facet
	dist = DotProduct( d->xyz, f->surface ) - f->surface[3];
	if ( fabs( dist ) > PLANAR_EPSILON ) {
		f->numBoundaries = 0;
		return qfalse;
	}

	// make boundaries
	f->numBoundaries = 4;

	CM_GenerateBoundaryForPoints( f->boundaries[0], f->surface, a->xyz, b->xyz );
	CM_GenerateBoundaryForPoints( f->boundaries[1], f->surface, b->xyz, c->xyz );
	CM_GenerateBoundaryForPoints( f->boundaries[2], f->surface, c->xyz, d->xyz );
	CM_GenerateBoundaryForPoints( f->boundaries[3], f->surface, d->xyz, a->xyz );

	VectorCopy( a->xyz, f->points[0] );
	VectorCopy( b->xyz, f->points[1] );
	VectorCopy( c->xyz, f->points[2] );
	VectorCopy( d->xyz, f->points[3] );

	for (i = 1; i < 4; i++)
	{
		if ( !PlaneFromPoints( plane, f->points[i], f->points[(i+1) % 4], f->points[(i+2) % 4]) ) {
			f->numBoundaries = 0;
			return qfalse;
		}

		if (DotProduct(f->surface, plane) < 0.9) {
			f->numBoundaries = 0;
			return qfalse;
		}
	}

	TextureMatrixFromPoints( f, a, b, c );

	return qtrue;
}