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
typedef  size_t u32 ;
struct tipc_node {size_t addr; } ;
struct cluster {size_t highest_node; struct tipc_node** nodes; } ;

/* Variables and functions */
 size_t tipc_node (size_t) ; 
 scalar_t__ tipc_node_has_active_links (struct tipc_node*) ; 

u32 tipc_cltr_next_node(struct cluster *c_ptr, u32 addr)
{
	struct tipc_node *n_ptr;
	u32 n_num = tipc_node(addr) + 1;

	if (!c_ptr)
		return addr;
	for (; n_num <= c_ptr->highest_node; n_num++) {
		n_ptr = c_ptr->nodes[n_num];
		if (n_ptr && tipc_node_has_active_links(n_ptr))
			return n_ptr->addr;
	}
	for (n_num = 1; n_num < tipc_node(addr); n_num++) {
		n_ptr = c_ptr->nodes[n_num];
		if (n_ptr && tipc_node_has_active_links(n_ptr))
			return n_ptr->addr;
	}
	return 0;
}