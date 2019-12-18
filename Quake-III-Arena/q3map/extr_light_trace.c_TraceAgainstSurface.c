#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ traceWork_t ;
struct TYPE_7__ {int numFacets; scalar_t__ facets; int /*<<< orphan*/  shader; int /*<<< orphan*/  radius; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ surfaceTest_t ;

/* Variables and functions */
 scalar_t__ SphereCull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TraceAgainstFacet (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  c_cullTrace ; 
 int c_testFacets ; 
 int /*<<< orphan*/  c_testTrace ; 
 int numthreads ; 

void	TraceAgainstSurface( traceWork_t *tw, surfaceTest_t *surf ) {
	int		i;

	// if surfaces are trans
	if ( SphereCull( tw->start, tw->end, surf->origin, surf->radius ) ) {
		if ( numthreads == 1 ) {
			c_cullTrace++;
		}
		return;
	}

	if ( numthreads == 1 ) {
		c_testTrace++;
		c_testFacets += surf->numFacets;
	}

	/*
	// MrE: backface culling
	if (!surf->patch && surf->numFacets) {
		// if the surface does not cast an alpha shadow
		if ( !(surf->shader->surfaceFlags & SURF_ALPHASHADOW) ) {
			vec3_t vec;
			VectorSubtract(tw->end, tw->start, vec);
			if (DotProduct(vec, surf->facets->surface) > 0)
				return;
		}
	}
	*/

	// test against each facet
	for ( i = 0 ; i < surf->numFacets ; i++ ) {
		TraceAgainstFacet( tw, surf->shader, surf->facets + i );
	}
}