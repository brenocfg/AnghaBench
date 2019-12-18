#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_7__ {float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ th_plane_t ;
struct TYPE_8__ {TYPE_1__* vertexes; } ;
struct TYPE_6__ {float* v; } ;

/* Variables and functions */
 float DotProduct (float*,int /*<<< orphan*/ ) ; 
 TYPE_3__ thworld ; 

int TH_IntersectTrianglePlanes(int v1, int v2, th_plane_t *triplane, th_plane_t *planes)
{
	float *p1, *p2, front, back, frac, d;
	int i, side, lastside;
	vec3_t mid;

	p1 = thworld.vertexes[v1].v;
	p2 = thworld.vertexes[v2].v;

	front = DotProduct(p1, triplane->normal) - triplane->dist;
	back = DotProduct(p2, triplane->normal) - triplane->dist;
	//if both points at the same side of the plane
	if (front < 0.1 && back < 0.1) return false;
	if (front > -0.1 && back > -0.1) return false;
	//
	frac = front/(front-back);
	mid[0] = p1[0] + (p2[0] - p1[0]) * frac;
	mid[1] = p1[1] + (p2[1] - p1[1]) * frac;
	mid[2] = p1[2] + (p2[2] - p1[2]) * frac;
	//if the mid point is at the same side of all the tri bounding planes
	lastside = 0;
	for (i = 0; i < 3; i++)
	{
		d = DotProduct(mid, planes[i].normal) - planes[i].dist;
		side = d < 0;
		if (i && side != lastside) return false;
		lastside = side;
	} //end for
	return true;
}