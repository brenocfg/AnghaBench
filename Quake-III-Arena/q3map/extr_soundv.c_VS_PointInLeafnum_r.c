#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  double vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {double dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ dplane_t ;
struct TYPE_7__ {size_t planeNum; int* children; } ;
typedef  TYPE_2__ dnode_t ;
struct TYPE_8__ {int cluster; } ;

/* Variables and functions */
 double DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* dleafs ; 
 TYPE_2__* dnodes ; 
 TYPE_1__* dplanes ; 

int	VS_PointInLeafnum_r(vec3_t point, int nodenum)
{
	int leafnum;
	vec_t	dist;
	dnode_t	*node;
	dplane_t	*plane;

	while (nodenum >= 0)
	{
		node = &dnodes[nodenum];
		plane = &dplanes[node->planeNum];
		dist = DotProduct (point, plane->normal) - plane->dist;
		if (dist > 0.1)
		{
			nodenum = node->children[0];
		}
		else if (dist < -0.1)
		{
			nodenum = node->children[1];
		}
		else
		{
			leafnum = VS_PointInLeafnum_r(point, node->children[0]);
			if (dleafs[leafnum].cluster != -1)
				return leafnum;
			nodenum = node->children[1];
		}
	}

	leafnum = -nodenum - 1;
	return leafnum;
}