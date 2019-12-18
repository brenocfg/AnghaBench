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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int /*<<< orphan*/  xyz; } ;
typedef  TYPE_1__ drawVert_t ;

/* Variables and functions */
 float COLINEAR_AREA ; 
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean	IsTriangleDegenerate( drawVert_t *points, int a, int b, int c ) {
	vec3_t		v1, v2, v3;
	float		d;

	VectorSubtract( points[b].xyz, points[a].xyz, v1 );
	VectorSubtract( points[c].xyz, points[a].xyz, v2 );
	CrossProduct( v1, v2, v3 );
	d = VectorLength( v3 );

	// assume all very small or backwards triangles will cause problems
	if ( d < COLINEAR_AREA ) {
		return qtrue;
	}

	return qfalse;
}