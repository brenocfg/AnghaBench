#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ dplane_t ;
struct TYPE_6__ {size_t planeNum; int* children; } ;
typedef  TYPE_2__ dnode_t ;

/* Variables and functions */
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dnodes ; 
 TYPE_1__* dplanes ; 

int	PointInLeafnum(vec3_t point)
{
	int		nodenum;
	vec_t	dist;
	dnode_t	*node;
	dplane_t	*plane;

	nodenum = 0;
	while (nodenum >= 0)
	{
		node = &dnodes[nodenum];
		plane = &dplanes[node->planeNum];
		dist = DotProduct (point, plane->normal) - plane->dist;
		if (dist > 0)
			nodenum = node->children[0];
		else
			nodenum = node->children[1];
	}

	return -nodenum - 1;
}