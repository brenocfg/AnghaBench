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
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ aas_plane_t ;
struct TYPE_7__ {int numedges; int firstedge; size_t planenum; } ;
typedef  TYPE_2__ aas_face_t ;
struct TYPE_8__ {size_t* v; } ;
typedef  TYPE_3__ aas_edge_t ;
struct TYPE_10__ {int numfaces; int numedges; int /*<<< orphan*/ * vertexes; TYPE_3__* edges; int /*<<< orphan*/ * edgeindex; TYPE_1__* planes; TYPE_2__* faces; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_DebugLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int LINECOLOR_BLUE ; 
 int LINECOLOR_GREEN ; 
 int LINECOLOR_RED ; 
 int LINECOLOR_YELLOW ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ aasworld ; 
 int abs (int /*<<< orphan*/ ) ; 
 TYPE_4__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 

void AAS_ShowFace(int facenum)
{
	int i, color, edgenum;
	aas_edge_t *edge;
	aas_face_t *face;
	aas_plane_t *plane;
	vec3_t start, end;

	color = LINECOLOR_YELLOW;
	//check if face number is in range
	if (facenum >= aasworld.numfaces)
	{
		botimport.Print(PRT_ERROR, "facenum %d out of range\n", facenum);
	} //end if
	face = &aasworld.faces[facenum];
	//walk through the edges of the face
	for (i = 0; i < face->numedges; i++)
	{
		//edge number
		edgenum = abs(aasworld.edgeindex[face->firstedge + i]);
		//check if edge number is in range
		if (edgenum >= aasworld.numedges)
		{
			botimport.Print(PRT_ERROR, "edgenum %d out of range\n", edgenum);
		} //end if
		edge = &aasworld.edges[edgenum];
		if (color == LINECOLOR_RED) color = LINECOLOR_GREEN;
		else if (color == LINECOLOR_GREEN) color = LINECOLOR_BLUE;
		else if (color == LINECOLOR_BLUE) color = LINECOLOR_YELLOW;
		else color = LINECOLOR_RED;
		AAS_DebugLine(aasworld.vertexes[edge->v[0]],
										aasworld.vertexes[edge->v[1]],
										color);
	} //end for
	plane = &aasworld.planes[face->planenum];
	edgenum = abs(aasworld.edgeindex[face->firstedge]);
	edge = &aasworld.edges[edgenum];
	VectorCopy(aasworld.vertexes[edge->v[0]], start);
	VectorMA(start, 20, plane->normal, end);
	AAS_DebugLine(start, end, LINECOLOR_RED);
}