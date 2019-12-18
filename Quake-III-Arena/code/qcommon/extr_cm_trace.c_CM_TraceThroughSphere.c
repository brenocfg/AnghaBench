#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_5__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
struct TYPE_6__ {float fraction; int /*<<< orphan*/  contents; TYPE_1__ plane; void* allsolid; void* startsolid; } ;
struct TYPE_7__ {TYPE_2__ trace; int /*<<< orphan*/  modelOrigin; } ;
typedef  TYPE_3__ traceWork_t ;

/* Variables and functions */
 float CM_DistanceFromLineSquared (float*,float*,float*,float*) ; 
 int /*<<< orphan*/  CONTENTS_BODY ; 
 int /*<<< orphan*/  DotProduct (int /*<<< orphan*/ ,float*) ; 
 float RADIUS_EPSILON ; 
 float SURFACE_CLIP_EPSILON ; 
 float Square (float) ; 
 float SquareRootFloat (float) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ ) ; 
 float VectorLength (float*) ; 
 float VectorLengthSquared (float*) ; 
 int /*<<< orphan*/  VectorMA (float*,float,float*,float*) ; 
 float VectorNormalize (float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 void* qtrue ; 

void CM_TraceThroughSphere( traceWork_t *tw, vec3_t origin, float radius, vec3_t start, vec3_t end ) {
	float l1, l2, length, scale, fraction;
	float a, b, c, d, sqrtd;
	vec3_t v1, dir, intersection;

	// if inside the sphere
	VectorSubtract(start, origin, dir);
	l1 = VectorLengthSquared(dir);
	if (l1 < Square(radius)) {
		tw->trace.fraction = 0;
		tw->trace.startsolid = qtrue;
		// test for allsolid
		VectorSubtract(end, origin, dir);
		l1 = VectorLengthSquared(dir);
		if (l1 < Square(radius)) {
			tw->trace.allsolid = qtrue;
		}
		return;
	}
	//
	VectorSubtract(end, start, dir);
	length = VectorNormalize(dir);
	//
	l1 = CM_DistanceFromLineSquared(origin, start, end, dir);
	VectorSubtract(end, origin, v1);
	l2 = VectorLengthSquared(v1);
	// if no intersection with the sphere and the end point is at least an epsilon away
	if (l1 >= Square(radius) && l2 > Square(radius+SURFACE_CLIP_EPSILON)) {
		return;
	}
	//
	//	| origin - (start + t * dir) | = radius
	//	a = dir[0]^2 + dir[1]^2 + dir[2]^2;
	//	b = 2 * (dir[0] * (start[0] - origin[0]) + dir[1] * (start[1] - origin[1]) + dir[2] * (start[2] - origin[2]));
	//	c = (start[0] - origin[0])^2 + (start[1] - origin[1])^2 + (start[2] - origin[2])^2 - radius^2;
	//
	VectorSubtract(start, origin, v1);
	// dir is normalized so a = 1
	a = 1.0f;//dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2];
	b = 2.0f * (dir[0] * v1[0] + dir[1] * v1[1] + dir[2] * v1[2]);
	c = v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2] - (radius+RADIUS_EPSILON) * (radius+RADIUS_EPSILON);

	d = b * b - 4.0f * c;// * a;
	if (d > 0) {
		sqrtd = SquareRootFloat(d);
		// = (- b + sqrtd) * 0.5f; // / (2.0f * a);
		fraction = (- b - sqrtd) * 0.5f; // / (2.0f * a);
		//
		if (fraction < 0) {
			fraction = 0;
		}
		else {
			fraction /= length;
		}
		if ( fraction < tw->trace.fraction ) {
			tw->trace.fraction = fraction;
			VectorSubtract(end, start, dir);
			VectorMA(start, fraction, dir, intersection);
			VectorSubtract(intersection, origin, dir);
			#ifdef CAPSULE_DEBUG
				l2 = VectorLength(dir);
				if (l2 < radius) {
					int bah = 1;
				}
			#endif
			scale = 1 / (radius+RADIUS_EPSILON);
			VectorScale(dir, scale, dir);
			VectorCopy(dir, tw->trace.plane.normal);
			VectorAdd( tw->modelOrigin, intersection, intersection);
			tw->trace.plane.dist = DotProduct(tw->trace.plane.normal, intersection);
			tw->trace.contents = CONTENTS_BODY;
		}
	}
	else if (d == 0) {
		//t1 = (- b ) / 2;
		// slide along the sphere
	}
	// no intersection at all
}