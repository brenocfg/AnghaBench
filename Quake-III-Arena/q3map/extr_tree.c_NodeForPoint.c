#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_6__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_7__ {size_t planenum; struct TYPE_7__** children; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t PLANENUM_LEAF ; 
 TYPE_1__* mapplanes ; 

node_t *NodeForPoint (node_t *node, vec3_t origin)
{
	plane_t	*plane;
	vec_t	d;

	while (node->planenum != PLANENUM_LEAF)
	{
		plane = &mapplanes[node->planenum];
		d = DotProduct (origin, plane->normal) - plane->dist;
		if (d >= 0)
			node = node->children[0];
		else
			node = node->children[1];
	}

	return node;
}