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
struct tipc_node {int /*<<< orphan*/  addr; } ;
struct cluster {size_t highest_node; struct tipc_node** nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ in_own_cluster (int /*<<< orphan*/ ) ; 
 size_t tipc_highest_allowed_slave ; 
 size_t tipc_max_nodes ; 
 size_t tipc_node (int /*<<< orphan*/ ) ; 

void tipc_cltr_attach_node(struct cluster *c_ptr, struct tipc_node *n_ptr)
{
	u32 n_num = tipc_node(n_ptr->addr);
	u32 max_n_num = tipc_max_nodes;

	if (in_own_cluster(n_ptr->addr))
		max_n_num = tipc_highest_allowed_slave;
	assert(n_num > 0);
	assert(n_num <= max_n_num);
	assert(c_ptr->nodes[n_num] == NULL);
	c_ptr->nodes[n_num] = n_ptr;
	if (n_num > c_ptr->highest_node)
		c_ptr->highest_node = n_num;
}