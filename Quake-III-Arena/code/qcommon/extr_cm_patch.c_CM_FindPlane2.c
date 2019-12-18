#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  signbits; int /*<<< orphan*/  plane; } ;

/* Variables and functions */
 scalar_t__ CM_PlaneEqual (TYPE_1__*,float*,int*) ; 
 int /*<<< orphan*/  CM_SignbitsForNormal (float*) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_PATCH_PLANES ; 
 int /*<<< orphan*/  Vector4Copy (float*,int /*<<< orphan*/ ) ; 
 int numPlanes ; 
 TYPE_1__* planes ; 
 int qfalse ; 

int CM_FindPlane2(float plane[4], int *flipped) {
	int i;

	// see if the points are close enough to an existing plane
	for ( i = 0 ; i < numPlanes ; i++ ) {
		if (CM_PlaneEqual(&planes[i], plane, flipped)) return i;
	}

	// add a new plane
	if ( numPlanes == MAX_PATCH_PLANES ) {
		Com_Error( ERR_DROP, "MAX_PATCH_PLANES" );
	}

	Vector4Copy( plane, planes[numPlanes].plane );
	planes[numPlanes].signbits = CM_SignbitsForNormal( plane );

	numPlanes++;

	*flipped = qfalse;

	return numPlanes-1;
}