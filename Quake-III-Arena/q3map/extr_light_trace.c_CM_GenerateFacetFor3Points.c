#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_11__ {int /*<<< orphan*/  xyz; } ;
typedef  TYPE_1__ drawVert_t ;
struct TYPE_12__ {int numBoundaries; int /*<<< orphan*/ * points; int /*<<< orphan*/  surface; int /*<<< orphan*/ * boundaries; } ;
typedef  TYPE_2__ cFacet_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_GenerateBoundaryForPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlaneFromPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TextureMatrixFromPoints (TYPE_2__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean CM_GenerateFacetFor3Points( cFacet_t *f, drawVert_t *a, drawVert_t *b, drawVert_t *c ) {
	// if we can't generate a valid plane for the points, ignore the facet
	if ( !PlaneFromPoints( f->surface, a->xyz, b->xyz, c->xyz ) ) {
		f->numBoundaries = 0;
		return qfalse;
	}

	// make boundaries
	f->numBoundaries = 3;

	CM_GenerateBoundaryForPoints( f->boundaries[0], f->surface, a->xyz, b->xyz );
	CM_GenerateBoundaryForPoints( f->boundaries[1], f->surface, b->xyz, c->xyz );
	CM_GenerateBoundaryForPoints( f->boundaries[2], f->surface, c->xyz, a->xyz );

	VectorCopy( a->xyz, f->points[0] );
	VectorCopy( b->xyz, f->points[1] );
	VectorCopy( c->xyz, f->points[2] );

	TextureMatrixFromPoints( f, a, b, c );

	return qtrue;
}