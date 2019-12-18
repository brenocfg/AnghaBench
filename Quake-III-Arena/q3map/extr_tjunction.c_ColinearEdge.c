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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 float VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean ColinearEdge( vec3_t v1, vec3_t v2, vec3_t v3 ) {
	vec3_t	midpoint, dir, offset, on;
	float	d;

	VectorSubtract( v2, v1, midpoint );
	VectorSubtract( v3, v1, dir );
	d = VectorNormalize( dir, dir );
	if ( d == 0 ) {
		return qfalse;	// degenerate
	}

	d = DotProduct( midpoint, dir );
	VectorScale( dir, d, on );
	VectorSubtract( midpoint, on, offset );
	d = VectorLength ( offset );

	if ( d < 0.1 ) {
		return qtrue;
	}

	return qfalse;
}