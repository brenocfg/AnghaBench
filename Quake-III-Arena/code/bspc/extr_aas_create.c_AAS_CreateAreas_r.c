#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ planenum; struct TYPE_8__** children; } ;
typedef  TYPE_1__ tmp_node_t ;
struct TYPE_9__ {scalar_t__ planenum; int contents; struct TYPE_9__** children; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 TYPE_1__* AAS_AllocTmpNode () ; 
 TYPE_1__* AAS_CreateArea (TYPE_2__*) ; 
 int CONTENTS_SOLID ; 
 scalar_t__ PLANENUM_LEAF ; 

tmp_node_t *AAS_CreateAreas_r(node_t *node)
{
	tmp_node_t *tmpnode;

	//recurse down to leafs
	if (node->planenum != PLANENUM_LEAF)
	{
		//the first tmp node is a dummy
		tmpnode = AAS_AllocTmpNode();
		tmpnode->planenum = node->planenum;
		tmpnode->children[0] = AAS_CreateAreas_r(node->children[0]);
		tmpnode->children[1] = AAS_CreateAreas_r(node->children[1]);
		return tmpnode;
	} //end if
	//areas won't be created for solid leafs
	if (node->contents & CONTENTS_SOLID)
	{
		//just return zero for a solid leaf (in tmp AAS NULL is a solid leaf)
		return NULL;
	} //end if

	return AAS_CreateArea(node);
}