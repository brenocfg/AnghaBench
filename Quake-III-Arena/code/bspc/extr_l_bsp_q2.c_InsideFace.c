#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_7__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ dplane_t ;
struct TYPE_8__ {int numedges; int firstedge; size_t planenum; } ;
typedef  TYPE_2__ dface_t ;
struct TYPE_10__ {size_t* v; } ;
struct TYPE_9__ {int /*<<< orphan*/ * point; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float DotProduct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float WCONVEX_EPSILON ; 
 size_t abs (int) ; 
 TYPE_5__* dedges ; 
 TYPE_1__* dplanes ; 
 int* dsurfedges ; 
 TYPE_3__* dvertexes ; 

int InsideFace(dface_t *face, vec3_t point)
{
	int i, edgenum, side;
	float dist;
	vec_t *v1, *v2;
	vec3_t normal, edgevec;
	dplane_t *plane;

	for (i = 0; i < face->numedges; i++)
	{
		//get the first and second vertex of the edge
		edgenum = dsurfedges[face->firstedge + i];
		side = edgenum < 0;
		v1 = dvertexes[dedges[abs(edgenum)].v[side]].point;
		v2 = dvertexes[dedges[abs(edgenum)].v[!side]].point;
		//create a plane through the edge vector, orthogonal to the face plane
		//and with the normal vector pointing out of the face
		VectorSubtract(v1, v2, edgevec);
		plane = &dplanes[face->planenum];
		CrossProduct(plane->normal, edgevec, normal);
		VectorNormalize(normal);
		dist = DotProduct(normal, v1);
		//
		if (DotProduct(normal, point) - dist > WCONVEX_EPSILON) return false;
	} //end for
	return true;
}