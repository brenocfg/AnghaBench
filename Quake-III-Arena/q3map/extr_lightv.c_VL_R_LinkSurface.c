#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_8__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_9__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ dplane_t ;
struct TYPE_10__ {size_t planeNum; int* children; } ;
typedef  TYPE_3__ dnode_t ;
struct TYPE_11__ {int cluster; } ;

/* Variables and functions */
 int SIDE_BACK ; 
 int SIDE_FRONT ; 
 int SIDE_ON ; 
 int /*<<< orphan*/  VL_LinkSurfaceIntoCluster (int,int) ; 
 int VL_SplitWinding (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,double) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* dleafs ; 
 TYPE_3__* dnodes ; 
 TYPE_2__* dplanes ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void VL_R_LinkSurface(int nodenum, int surfaceNum, winding_t *w)
{
	int leafnum, cluster, res;
	dnode_t *node;
	dplane_t *plane;
	winding_t back;
	plane_t split;

	while(nodenum >= 0)
	{
		node = &dnodes[nodenum];
		plane = &dplanes[node->planeNum];

		VectorCopy(plane->normal, split.normal);
		split.dist = plane->dist;
		res = VL_SplitWinding (w, &back, &split, 0.1);

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
			memcpy(&back, w, sizeof(winding_t));
			VL_R_LinkSurface(node->children[1], surfaceNum, &back);
			nodenum = node->children[0];
		}
		else
		{
			VL_R_LinkSurface(node->children[1], surfaceNum, &back);
			nodenum = node->children[0];
		}
	}
	leafnum = -nodenum - 1;
	cluster = dleafs[leafnum].cluster;
	if (cluster != -1)
	{
		VL_LinkSurfaceIntoCluster(cluster, surfaceNum);
	}
}