#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_15__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
typedef  TYPE_1__ q1_dplane_t ;
struct TYPE_16__ {size_t planenum; int numedges; int firstedge; scalar_t__ side; } ;
typedef  TYPE_2__ q1_dface_t ;
struct TYPE_17__ {struct TYPE_17__* next; int /*<<< orphan*/  side; } ;
typedef  TYPE_3__ bspbrush_t ;
struct TYPE_19__ {size_t* v; } ;
struct TYPE_18__ {int /*<<< orphan*/ * point; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int FindFloatPlane (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  FreeBrush (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeBrushList (TYPE_3__*) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 int /*<<< orphan*/  SplitBrush (TYPE_3__*,int,TYPE_3__**,TYPE_3__**) ; 
 int /*<<< orphan*/  VectorNegate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t abs (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 TYPE_5__* q1_dedges ; 
 int /*<<< orphan*/ * q1_dplanes ; 
 int* q1_dsurfedges ; 
 TYPE_4__* q1_dvertexes ; 

bspbrush_t *Q1_SplitBrushWithFace(bspbrush_t *brush, q1_dface_t *face)
{
	int i, edgenum, side, planenum, splits;
	float dist;
	q1_dplane_t plane;
	vec_t *v1, *v2;
	vec3_t normal, edgevec;
	bspbrush_t *front, *back, *brushlist;

	memcpy(&plane, &q1_dplanes[face->planenum], sizeof(q1_dplane_t));
	//check on which side of the plane the face is
	if (face->side)
	{
		VectorNegate(plane.normal, plane.normal);
		plane.dist = -plane.dist;
	} //end if
	splits = 0;
	brushlist = NULL;
	for (i = 0; i < face->numedges; i++)
	{
		//get the first and second vertex of the edge
		edgenum = q1_dsurfedges[face->firstedge + i];
		side = edgenum > 0;
		//if the face plane is flipped
		v1 = q1_dvertexes[q1_dedges[abs(edgenum)].v[side]].point;
		v2 = q1_dvertexes[q1_dedges[abs(edgenum)].v[!side]].point;
		//create a plane through the edge vector, orthogonal to the face plane
		//and with the normal vector pointing out of the face
		VectorSubtract(v1, v2, edgevec);
		CrossProduct(edgevec, plane.normal, normal);
		VectorNormalize(normal);
		dist = DotProduct(normal, v1);
		//
		planenum = FindFloatPlane(normal, dist);
		//split the current brush
		SplitBrush(brush, planenum, &front, &back);
		//if there is a back brush just put it in the list
		if (back)
		{
			//copy the brush contents
			back->side = brush->side;
			//
			back->next = brushlist;
			brushlist = back;
			splits++;
		} //end if
		if (!front)
		{
			Log_Print("Q1_SplitBrushWithFace: no new brush\n");
			FreeBrushList(brushlist);
			return NULL;
		} //end if
		//copy the brush contents
		front->side = brush->side;
		//continue splitting the front brush
		brush = front;
	} //end for
	if (!splits)
	{
		FreeBrush(front);
		return NULL;
	} //end if
	front->next = brushlist;
	brushlist = front;
	return brushlist;
}