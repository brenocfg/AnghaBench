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
struct TYPE_4__ {int numpoints; int /*<<< orphan*/ * points; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float WCONVEX_EPSILON ; 
 int qfalse ; 
 int qtrue ; 

int Winding_PlanesConcave(winding_t *w1, winding_t *w2,
							 vec3_t normal1, vec3_t normal2,
							 float dist1, float dist2)
{
	int i;

	if (!w1 || !w2) return qfalse;

	// check if one of the points of winding 1 is at the front of the plane of winding 2
	for (i = 0; i < w1->numpoints; i++)
	{
		if (DotProduct(normal2, w1->points[i]) - dist2 > WCONVEX_EPSILON) return qtrue;
	}
	// check if one of the points of winding 2 is at the front of the plane of winding 1
	for (i = 0; i < w2->numpoints; i++)
	{
		if (DotProduct(normal1, w2->points[i]) - dist1 > WCONVEX_EPSILON) return qtrue;
	}

	return qfalse;
}