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
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean	SphereCull( vec3_t start, vec3_t stop, vec3_t origin, float radius ) {
	vec3_t		v;
	float		d;
	vec3_t		dir;
	float		len;
	vec3_t		on;

	VectorSubtract( stop, start, dir );
	len = VectorNormalize( dir, dir );

	VectorSubtract( origin, start, v );
	d = DotProduct( v, dir );
	if ( d > len + radius ) {
		return qtrue;		// too far ahead
	}
	if ( d < -radius ) {
		return qtrue;		// too far behind
	}
	VectorMA( start, d, dir, on );
	
	VectorSubtract( on, origin, v );

	len = VectorLength( v );

	if ( len > radius ) {
		return qtrue;		// too far to the side
	}

	return qfalse;		// must be traced against
}