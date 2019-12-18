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
struct TYPE_8__ {scalar_t__ planenum; TYPE_1__* portals; struct TYPE_8__** children; } ;
typedef  TYPE_2__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreePortal (TYPE_1__*) ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  RemovePortalFromNode (TYPE_1__*,TYPE_2__*) ; 

void FreeTreePortals_r (node_t *node)
{
	portal_t	*p, *nextp;
	int			s;

	// free children
	if (node->planenum != PLANENUM_LEAF)
	{
		FreeTreePortals_r (node->children[0]);
		FreeTreePortals_r (node->children[1]);
	}

	// free portals
	for (p=node->portals ; p ; p=nextp)
	{
		s = (p->nodes[1] == node);
		nextp = p->next[s];

		RemovePortalFromNode (p, p->nodes[!s]);
		FreePortal (p);
	}
	node->portals = NULL;
}