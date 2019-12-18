#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int MAX_NUMNODES ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int first_node (int /*<<< orphan*/ ) ; 
 int next_node (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int next_node_allowed(int nid, nodemask_t *nodes_allowed)
{
	nid = next_node(nid, *nodes_allowed);
	if (nid == MAX_NUMNODES)
		nid = first_node(*nodes_allowed);
	VM_BUG_ON(nid >= MAX_NUMNODES);

	return nid;
}