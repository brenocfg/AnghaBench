#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ planenum; struct TYPE_5__** children; scalar_t__ detail_seperator; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  MakeNodePortal (TYPE_1__*) ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  SplitNodePortals (TYPE_1__*) ; 

void CreateVisPortals_r (node_t *node)
{
	// stop as soon as we get to a detail_seperator, which
	// means that everything below is in a single cluster
	if (node->planenum == PLANENUM_LEAF || node->detail_seperator )
		return;

	MakeNodePortal (node);
	SplitNodePortals (node);

	CreateVisPortals_r (node->children[0]);
	CreateVisPortals_r (node->children[1]);
}