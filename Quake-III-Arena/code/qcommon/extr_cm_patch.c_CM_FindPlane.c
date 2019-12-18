#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* plane; int /*<<< orphan*/  signbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_PlaneFromPoints (float*,float*,float*,float*) ; 
 int /*<<< orphan*/  CM_SignbitsForNormal (float*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DotProduct (float*,scalar_t__*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_PATCH_PLANES ; 
 float PLANE_TRI_EPSILON ; 
 int /*<<< orphan*/  Vector4Copy (float*,scalar_t__*) ; 
 int numPlanes ; 
 TYPE_1__* planes ; 

__attribute__((used)) static int CM_FindPlane( float *p1, float *p2, float *p3 ) {
	float	plane[4];
	int		i;
	float	d;

	if ( !CM_PlaneFromPoints( plane, p1, p2, p3 ) ) {
		return -1;
	}

	// see if the points are close enough to an existing plane
	for ( i = 0 ; i < numPlanes ; i++ ) {
		if ( DotProduct( plane, planes[i].plane ) < 0 ) {
			continue;	// allow backwards planes?
		}

		d = DotProduct( p1, planes[i].plane ) - planes[i].plane[3];
		if ( d < -PLANE_TRI_EPSILON || d > PLANE_TRI_EPSILON ) {
			continue;
		}

		d = DotProduct( p2, planes[i].plane ) - planes[i].plane[3];
		if ( d < -PLANE_TRI_EPSILON || d > PLANE_TRI_EPSILON ) {
			continue;
		}

		d = DotProduct( p3, planes[i].plane ) - planes[i].plane[3];
		if ( d < -PLANE_TRI_EPSILON || d > PLANE_TRI_EPSILON ) {
			continue;
		}

		// found it
		return i;
	}

	// add a new plane
	if ( numPlanes == MAX_PATCH_PLANES ) {
		Com_Error( ERR_DROP, "MAX_PATCH_PLANES" );
	}

	Vector4Copy( plane, planes[numPlanes].plane );
	planes[numPlanes].signbits = CM_SignbitsForNormal( plane );

	numPlanes++;

	return numPlanes-1;
}