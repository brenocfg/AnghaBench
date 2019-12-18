#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/ * vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_5__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ aas_plane_t ;
struct TYPE_6__ {size_t planenum; int numedges; int firstedge; } ;
typedef  TYPE_2__ aas_face_t ;
struct TYPE_7__ {size_t* v; } ;
typedef  TYPE_3__ aas_edge_t ;
struct TYPE_8__ {int* edgeindex; int /*<<< orphan*/ ** vertexes; TYPE_3__* edges; TYPE_1__* planes; TYPE_2__* faces; int /*<<< orphan*/  loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 float DotProduct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ aasworld ; 
 size_t abs (int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean AAS_PointInsideFace(int facenum, vec3_t point, float epsilon)
{
	int i, firstvertex, edgenum;
	vec_t *v1, *v2;
	vec3_t edgevec, pointvec, sepnormal;
	aas_edge_t *edge;
	aas_plane_t *plane;
	aas_face_t *face;

	if (!aasworld.loaded) return qfalse;

	face = &aasworld.faces[facenum];
	plane = &aasworld.planes[face->planenum];
	//
	for (i = 0; i < face->numedges; i++)
	{
		edgenum = aasworld.edgeindex[face->firstedge + i];
		edge = &aasworld.edges[abs(edgenum)];
		//get the first vertex of the edge
		firstvertex = edgenum < 0;
		v1 = aasworld.vertexes[edge->v[firstvertex]];
		v2 = aasworld.vertexes[edge->v[!firstvertex]];
		//edge vector
		VectorSubtract(v2, v1, edgevec);
		//vector from first edge point to point possible in face
		VectorSubtract(point, v1, pointvec);
		//
		CrossProduct(edgevec, plane->normal, sepnormal);
		//
		if (DotProduct(pointvec, sepnormal) < -epsilon) return qfalse;
	} //end for
	return qtrue;
}