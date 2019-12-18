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
struct TYPE_6__ {struct TYPE_6__** children; scalar_t__ planenum; TYPE_2__* tmparea; } ;
typedef  TYPE_1__ tmp_node_t ;
struct TYPE_7__ {struct TYPE_7__* mergedarea; } ;
typedef  TYPE_2__ tmp_area_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_FreeTmpNode (TYPE_1__*) ; 
 int /*<<< orphan*/  c_numprunes ; 

tmp_node_t *AAS_PruneNodes_r(tmp_node_t *tmpnode)
{
	tmp_area_t *tmparea1, *tmparea2;

	//if it is a solid leaf
	if (!tmpnode) return NULL;
	//
	if (tmpnode->tmparea) return tmpnode;
	//process the children first
	tmpnode->children[0] = AAS_PruneNodes_r(tmpnode->children[0]);
	tmpnode->children[1] = AAS_PruneNodes_r(tmpnode->children[1]);
	//if both children are areas
	if (tmpnode->children[0] && tmpnode->children[1] &&
			tmpnode->children[0]->tmparea && tmpnode->children[1]->tmparea)
	{
		tmparea1 = tmpnode->children[0]->tmparea;
		while(tmparea1->mergedarea) tmparea1 = tmparea1->mergedarea;

		tmparea2 = tmpnode->children[1]->tmparea;
		while(tmparea2->mergedarea) tmparea2 = tmparea2->mergedarea;

		if (tmparea1 == tmparea2)
		{
			c_numprunes++;
			tmpnode->tmparea = tmparea1;
			tmpnode->planenum = 0;
			AAS_FreeTmpNode(tmpnode->children[0]);
			AAS_FreeTmpNode(tmpnode->children[1]);
			tmpnode->children[0] = NULL;
			tmpnode->children[1] = NULL;
			return tmpnode;
		} //end if
	} //end if
	//if both solid leafs
	if (!tmpnode->children[0] && !tmpnode->children[1])
	{
		c_numprunes++;
		AAS_FreeTmpNode(tmpnode);
		return NULL;
	} //end if
	//
	return tmpnode;
}