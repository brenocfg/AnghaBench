#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int planenum; struct TYPE_6__** children; int /*<<< orphan*/ * tmparea; } ;
typedef  TYPE_1__ tmp_node_t ;
typedef  int /*<<< orphan*/  tmp_area_t ;

/* Variables and functions */

tmp_node_t *AAS_RefreshLadderSubdividedTree_r(tmp_node_t *tmpnode, tmp_area_t *tmparea,
												  tmp_node_t *tmpnode1, tmp_node_t *tmpnode2, int planenum)
{
	//if this is a solid leaf
	if (!tmpnode) return NULL;
	//negative so it's an area
	if (tmpnode->tmparea)
	{
		if (tmpnode->tmparea == tmparea)
		{
			tmpnode->tmparea = NULL;
			tmpnode->planenum = planenum;
			tmpnode->children[0] = tmpnode1;
			tmpnode->children[1] = tmpnode2;
		} //end if
		return tmpnode;
	} //end if
	//do the children recursively
	tmpnode->children[0] = AAS_RefreshLadderSubdividedTree_r(tmpnode->children[0],
									tmparea, tmpnode1, tmpnode2, planenum);
	tmpnode->children[1] = AAS_RefreshLadderSubdividedTree_r(tmpnode->children[1],
									tmparea, tmpnode1, tmpnode2, planenum);
	return tmpnode;
}