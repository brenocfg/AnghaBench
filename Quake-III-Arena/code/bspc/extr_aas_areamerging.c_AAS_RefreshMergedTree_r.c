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
struct TYPE_5__ {struct TYPE_5__** children; TYPE_2__* tmparea; } ;
typedef  TYPE_1__ tmp_node_t ;
struct TYPE_6__ {struct TYPE_6__* mergedarea; } ;
typedef  TYPE_2__ tmp_area_t ;

/* Variables and functions */

tmp_node_t *AAS_RefreshMergedTree_r(tmp_node_t *tmpnode)
{
	tmp_area_t *tmparea;

	//if this is a solid leaf
	if (!tmpnode) return NULL;
	//if this is an area leaf
	if (tmpnode->tmparea)
	{
		tmparea = tmpnode->tmparea;
		while(tmparea->mergedarea) tmparea = tmparea->mergedarea;
		tmpnode->tmparea = tmparea;
		return tmpnode;
	} //end if
	//do the children recursively
	tmpnode->children[0] = AAS_RefreshMergedTree_r(tmpnode->children[0]);
	tmpnode->children[1] = AAS_RefreshMergedTree_r(tmpnode->children[1]);
	return tmpnode;
}