#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__** nodes; struct TYPE_7__** next; } ;
typedef  TYPE_1__ portal_t ;
struct TYPE_8__ {int occupied; TYPE_1__* portals; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  P_AddNodeToList (TYPE_2__*) ; 
 TYPE_2__* P_NextNodeFromList () ; 
 int /*<<< orphan*/  Portal_EntityFlood (TYPE_1__*,int) ; 

void FloodPortals(node_t *firstnode)
{
	node_t *node;
	portal_t *p;
	int s;

	firstnode->occupied = 1;
	P_AddNodeToList(firstnode);

	for (node = P_NextNodeFromList(); node; node = P_NextNodeFromList())
	{
		for (p = node->portals; p; p = p->next[s])
		{
			s = (p->nodes[1] == node);
			//if the node at the other side of the portal is occupied already
			if (p->nodes[!s]->occupied) continue;
			//if it isn't possible to flood through this portal
			if (!Portal_EntityFlood(p, s)) continue;
			//
			p->nodes[!s]->occupied = node->occupied + 1;
			//
			P_AddNodeToList(p->nodes[!s]);
		} //end for
	} //end for
}