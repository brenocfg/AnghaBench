#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* side; int /*<<< orphan*/  sidefound; int /*<<< orphan*/  onnode; TYPE_3__** nodes; struct TYPE_7__** next; } ;
typedef  TYPE_2__ portal_t ;
struct TYPE_8__ {scalar_t__ planenum; TYPE_2__* portals; int /*<<< orphan*/  contents; struct TYPE_8__** children; } ;
typedef  TYPE_3__ node_t ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FindPortalSide (TYPE_2__*) ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  SFL_VISIBLE ; 

void MarkVisibleSides_r (node_t *node)
{
	portal_t *p;
	int s;

	if (node->planenum != PLANENUM_LEAF)
	{
		MarkVisibleSides_r (node->children[0]);
		MarkVisibleSides_r (node->children[1]);
		return;
	} //end if

	// empty leaves are never boundary leaves
	if (!node->contents) return;

	// see if there is a visible face
	for (p=node->portals ; p ; p = p->next[!s])
	{
		s = (p->nodes[0] == node);
		if (!p->onnode)
			continue;		// edge of world
		if (!p->sidefound)
			FindPortalSide (p);
		if (p->side)
			p->side->flags |= SFL_VISIBLE;
	} //end for
}