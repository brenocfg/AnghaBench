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
struct TYPE_6__ {scalar_t__ planenum; struct TYPE_6__** children; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_1__ node_t ;
struct TYPE_7__ {int planeNum; int* children; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_2__ dnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EmitLeaf (TYPE_1__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_NODES ; 
 scalar_t__ PLANENUM_LEAF ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dnodes ; 
 int numleafs ; 
 size_t numnodes ; 

int EmitDrawNode_r (node_t *node)
{
	dnode_t	*n;
	int		i;

	if (node->planenum == PLANENUM_LEAF)
	{
		EmitLeaf (node);
		return -numleafs;
	}

	// emit a node	
	if (numnodes == MAX_MAP_NODES)
		Error ("MAX_MAP_NODES");
	n = &dnodes[numnodes];
	numnodes++;

	VectorCopy (node->mins, n->mins);
	VectorCopy (node->maxs, n->maxs);

	if (node->planenum & 1)
		Error ("WriteDrawNodes_r: odd planenum");
	n->planeNum = node->planenum;

	//
	// recursively output the other nodes
	//	
	for (i=0 ; i<2 ; i++)
	{
		if (node->children[i]->planenum == PLANENUM_LEAF)
		{
			n->children[i] = -(numleafs + 1);
			EmitLeaf (node->children[i]);
		}
		else
		{
			n->children[i] = numnodes;	
			EmitDrawNode_r (node->children[i]);
		}
	}

	return n - dnodes;
}