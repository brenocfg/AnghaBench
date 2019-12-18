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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {int numedges; int firstedge; } ;
typedef  TYPE_1__ aas_face_t ;
struct TYPE_6__ {size_t* v; } ;
typedef  TYPE_2__ aas_edge_t ;
struct TYPE_7__ {int* edgeindex; int /*<<< orphan*/ * vertexes; TYPE_2__* edges; } ;

/* Variables and functions */
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 TYPE_3__ aasworld ; 
 size_t abs (int) ; 

void TH_FaceCenter(aas_face_t *face, vec3_t center)
{
	int i, edgenum, side;
	aas_edge_t *edge;

	VectorClear(center);
	for (i = 0; i < face->numedges; i++)
	{
		edgenum = abs(aasworld.edgeindex[face->firstedge + i]);
		side = edgenum < 0;
		edge = &aasworld.edges[abs(edgenum)];
		VectorAdd(aasworld.vertexes[edge->v[side]], center, center);
	} //end for
	VectorScale(center, 1.0 / face->numedges, center);
}