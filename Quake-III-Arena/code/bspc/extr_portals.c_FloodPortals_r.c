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
struct TYPE_5__ {TYPE_2__** nodes; struct TYPE_5__** next; } ;
typedef  TYPE_1__ portal_t ;
struct TYPE_6__ {int occupied; TYPE_1__* portals; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  Log_Print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Portal_EntityFlood (TYPE_1__*,int) ; 
 int /*<<< orphan*/  numrec ; 

void FloodPortals_r (node_t *node, int dist)
{
	portal_t *p;
	int s;
//	int i;

	Log_Print("\r%6d", ++numrec);

	if (node->occupied) Error("FloodPortals_r: node already occupied\n");
	if (!node)
	{
		Error("FloodPortals_r: NULL node\n");
	} //end if*/
	node->occupied = dist;

	for (p = node->portals; p; p = p->next[s])
	{
		s = (p->nodes[1] == node);
		//if the node at the other side of the portal is occupied already
		if (p->nodes[!s]->occupied) continue;
		//if it isn't possible to flood through this portal
		if (!Portal_EntityFlood(p, s)) continue;
		//flood recursively through the current portal
		FloodPortals_r(p->nodes[!s], dist+1);
	} //end for
	Log_Print("\r%6d", --numrec);
}