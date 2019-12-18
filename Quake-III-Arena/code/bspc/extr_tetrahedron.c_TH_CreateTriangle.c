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
struct TYPE_6__ {size_t planenum; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  planes; int /*<<< orphan*/ * hashnext; int /*<<< orphan*/ * next; int /*<<< orphan*/ * prev; scalar_t__ back; scalar_t__ front; int /*<<< orphan*/ * edges; } ;
typedef  TYPE_2__ th_triangle_t ;
struct TYPE_7__ {int numtriangles; TYPE_1__* vertexes; int /*<<< orphan*/ * planes; TYPE_2__* triangles; } ;
struct TYPE_5__ {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_TH_TRIANGLES ; 
 int /*<<< orphan*/  TH_AddEdgeUser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TH_AddTriangleToHash (TYPE_2__*) ; 
 int /*<<< orphan*/  TH_CreateTrianglePlanes (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TH_FindOrCreateEdge (int,int) ; 
 size_t TH_PlaneFromPoints (int,int,int) ; 
 int /*<<< orphan*/  abs (int /*<<< orphan*/ ) ; 
 TYPE_3__ thworld ; 

int TH_CreateTriangle(int verts[3])
{
	th_triangle_t *tri;
	int i;

	if (thworld.numtriangles == 0) thworld.numtriangles = 1;
	if (thworld.numtriangles >= MAX_TH_TRIANGLES)
		Error("MAX_TH_TRIANGLES");
	tri = &thworld.triangles[thworld.numtriangles++];
	for (i = 0; i < 3; i++)
	{
		tri->edges[i] = TH_FindOrCreateEdge(verts[i], verts[(i+1)%3]);
		TH_AddEdgeUser(abs(tri->edges[i]));
	} //end for
	tri->front = 0;
	tri->back = 0;
	tri->planenum = TH_PlaneFromPoints(verts[0], verts[1], verts[2]);
	tri->prev = NULL;
	tri->next = NULL;
	tri->hashnext = NULL;
	TH_CreateTrianglePlanes(verts, &thworld.planes[tri->planenum], tri->planes);
	TH_AddTriangleToHash(tri);
	ClearBounds(tri->mins, tri->maxs);
	for (i = 0; i < 3; i++)
	{
		AddPointToBounds(thworld.vertexes[verts[i]].v, tri->mins, tri->maxs);
	} //end for
	return thworld.numtriangles-1;
}