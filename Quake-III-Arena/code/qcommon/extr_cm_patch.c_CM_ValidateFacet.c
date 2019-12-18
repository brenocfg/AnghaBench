#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/ * vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int surfacePlane; int numBorders; int* borderPlanes; int /*<<< orphan*/ * borderInward; } ;
typedef  TYPE_1__ facet_t ;
struct TYPE_5__ {int /*<<< orphan*/  plane; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BaseWindingForPlane (float*,float) ; 
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,float*,float,float) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_MAP_BOUNDS ; 
 int /*<<< orphan*/  Vector4Copy (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,float*,float*) ; 
 int /*<<< orphan*/  WindingBounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* planes ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static qboolean CM_ValidateFacet( facet_t *facet ) {
	float		plane[4];
	int			j;
	winding_t	*w;
	vec3_t		bounds[2];

	if ( facet->surfacePlane == -1 ) {
		return qfalse;
	}

	Vector4Copy( planes[ facet->surfacePlane ].plane, plane );
	w = BaseWindingForPlane( plane,  plane[3] );
	for ( j = 0 ; j < facet->numBorders && w ; j++ ) {
		if ( facet->borderPlanes[j] == -1 ) {
			return qfalse;
		}
		Vector4Copy( planes[ facet->borderPlanes[j] ].plane, plane );
		if ( !facet->borderInward[j] ) {
			VectorSubtract( vec3_origin, plane, plane );
			plane[3] = -plane[3];
		}
		ChopWindingInPlace( &w, plane, plane[3], 0.1f );
	}

	if ( !w ) {
		return qfalse;		// winding was completely chopped away
	}

	// see if the facet is unreasonably large
	WindingBounds( w, bounds[0], bounds[1] );
	FreeWinding( w );
	
	for ( j = 0 ; j < 3 ; j++ ) {
		if ( bounds[1][j] - bounds[0][j] > MAX_MAP_BOUNDS ) {
			return qfalse;		// we must be missing a plane
		}
		if ( bounds[0][j] >= MAX_MAP_BOUNDS ) {
			return qfalse;
		}
		if ( bounds[1][j] <= -MAX_MAP_BOUNDS ) {
			return qfalse;
		}
	}
	return qtrue;		// winding is fine
}