#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_4__ {float* normal; float dist; } ;
typedef  TYPE_1__ plane_t ;

/* Variables and functions */
 scalar_t__ DIST_EPSILON ; 
 scalar_t__ NORMAL_EPSILON ; 
 scalar_t__ fabs (float) ; 
 int qfalse ; 
 int qtrue ; 

int Plane_Equal(plane_t *a, plane_t *b, int flip)
{
	vec3_t normal;
	float dist;

	if (flip) {
		normal[0] = - b->normal[0];
		normal[1] = - b->normal[1];
		normal[2] = - b->normal[2];
		dist = - b->dist;
	}
	else {
		normal[0] = b->normal[0];
		normal[1] = b->normal[1];
		normal[2] = b->normal[2];
		dist = b->dist;
	}
	if (
	   fabs(a->normal[0] - normal[0]) < NORMAL_EPSILON
	&& fabs(a->normal[1] - normal[1]) < NORMAL_EPSILON
	&& fabs(a->normal[2] - normal[2]) < NORMAL_EPSILON
	&& fabs(a->dist - dist) < DIST_EPSILON )
		return qtrue;
	return qfalse;
}