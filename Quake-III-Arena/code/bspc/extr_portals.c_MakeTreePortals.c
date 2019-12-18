#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  Log_Write (char*,scalar_t__) ; 
 int /*<<< orphan*/  MakeHeadnodePortals (TYPE_1__*) ; 
 int /*<<< orphan*/  MakeTreePortals_r (int /*<<< orphan*/ ) ; 
 int WindingMemory () ; 
 scalar_t__ c_numportalizednodes ; 
 int c_portalmemory ; 
 int c_tinyportals ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

void MakeTreePortals(tree_t *tree)
{

#ifdef ME
	Log_Print("---- Node Portalization ----\n");
	c_numportalizednodes = 0;
	c_portalmemory = 0;
	qprintf("%6d nodes portalized", c_numportalizednodes);
#endif //ME

	MakeHeadnodePortals(tree);
	MakeTreePortals_r(tree->headnode);

#ifdef ME
	qprintf("\n");
	Log_Write("%6d nodes portalized\r\n", c_numportalizednodes);
	Log_Print("%6d tiny portals\r\n", c_tinyportals);
	Log_Print("%6d KB of portal memory\r\n", c_portalmemory >> 10);
	Log_Print("%6i KB of winding memory\r\n", WindingMemory() >> 10);
#endif //ME
}