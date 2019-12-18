#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (float*,int /*<<< orphan*/ ,float*) ; 
 float DotProduct (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CM_GenerateBoundaryForPoints( float boundary[4], float plane[4], vec3_t a, vec3_t b ) {
	vec3_t	d1;

	// amke a perpendicular vector to the edge and the surface
	VectorSubtract( b, a, d1 );
	CrossProduct( plane, d1, boundary );
	VectorNormalize( boundary, boundary );
	boundary[3] = DotProduct( a, boundary );
}