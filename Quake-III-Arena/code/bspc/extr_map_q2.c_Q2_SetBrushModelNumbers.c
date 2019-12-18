#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t modelnum; } ;
typedef  TYPE_1__ entity_t ;
struct TYPE_7__ {int headnode; } ;
struct TYPE_6__ {int* children; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q2_InitNodeStack () ; 
 int Q2_PopNodeStack () ; 
 int /*<<< orphan*/  Q2_PushNodeStack (int) ; 
 int /*<<< orphan*/  Q2_SetLeafBrushesModelNumbers (int,size_t) ; 
 TYPE_3__* dmodels ; 
 TYPE_2__* dnodes ; 

void Q2_SetBrushModelNumbers(entity_t *mapent)
{
	int n, pn;
	int leafnum;

	//
	Q2_InitNodeStack();
	//head node (root) of the bsp tree
	n = dmodels[mapent->modelnum].headnode;
	pn = 0;
	
	do
	{
		//if we are in a leaf (negative node number)
		if (n < 0)
		{
			//number of the leaf
			leafnum = (-n) - 1;
			//set the brush numbers
			Q2_SetLeafBrushesModelNumbers(leafnum, mapent->modelnum);
			//walk back into the tree to find a second child to continue with
			for (pn = Q2_PopNodeStack(); pn >= 0; n = pn, pn = Q2_PopNodeStack())
			{
				//if we took the first child at the parent node
				if (dnodes[pn].children[0] == n) break;
			} //end for
			//if the stack wasn't empty (if not processed whole tree)
			if (pn >= 0)
			{
				//push the parent node again
				Q2_PushNodeStack(pn);
				//we proceed with the second child of the parent node
				n = dnodes[pn].children[1];
			} //end if
		} //end if
		else
		{
			//push the current node onto the stack
			Q2_PushNodeStack(n);
			//walk forward into the tree to the first child
			n = dnodes[n].children[0];
		} //end else
	} while(pn >= 0);
}