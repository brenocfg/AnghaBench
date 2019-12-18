#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_10__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
typedef  TYPE_2__ dplane_t ;
struct TYPE_11__ {size_t planeNum; int* children; } ;
typedef  TYPE_3__ dnode_t ;
struct TYPE_12__ {int cluster; size_t firstLeafBrush; int /*<<< orphan*/  numLeafBrushes; } ;
typedef  TYPE_4__ dleaf_t ;

/* Variables and functions */
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SIDE_BACK ; 
 int SIDE_FRONT ; 
 int SIDE_ON ; 
 int VS_SplitWinding (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,double) ; 
 scalar_t__ VS_WindingAreaOutsideBrushes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dleafbrushes ; 
 TYPE_4__* dleafs ; 
 TYPE_3__* dnodes ; 
 TYPE_2__* dplanes ; 

float VS_R_WindingAreaOutsideSolid(winding_t *w, vec3_t normal, int nodenum)
{
	int leafnum, res;
	float area;
	dnode_t *node;
	dleaf_t *leaf;
	dplane_t *plane;
	winding_t back;
	plane_t split;

	area = 0;
	while(nodenum >= 0)
	{
		node = &dnodes[nodenum];
		plane = &dplanes[node->planeNum];

		VectorCopy(plane->normal, split.normal);
		split.dist = plane->dist;
		res = VS_SplitWinding (w, &back, &split, 0.1);

		if (res == SIDE_FRONT)
		{
			nodenum = node->children[0];
		}
		else if (res == SIDE_BACK)
		{
			nodenum = node->children[1];
		}
		else if (res == SIDE_ON)
		{
			if (DotProduct(normal, plane->normal) > 0)
				nodenum = node->children[0];
			else
				nodenum = node->children[1];
		}
		else
		{
			area += VS_R_WindingAreaOutsideSolid(&back, normal, node->children[1]);
			nodenum = node->children[0];
		}
	}
	leafnum = -nodenum - 1;
	leaf = &dleafs[leafnum];
	if (leaf->cluster != -1)
	{
		area += VS_WindingAreaOutsideBrushes(w, &dleafbrushes[leaf->firstLeafBrush], leaf->numLeafBrushes);
	}
	return area;
}