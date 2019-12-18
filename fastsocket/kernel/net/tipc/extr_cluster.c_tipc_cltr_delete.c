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
struct cluster {size_t highest_node; size_t highest_slave; struct cluster* nodes; } ;

/* Variables and functions */
 size_t LOWEST_SLAVE ; 
 int /*<<< orphan*/  kfree (struct cluster*) ; 
 int /*<<< orphan*/  tipc_node_delete (struct cluster) ; 

void tipc_cltr_delete(struct cluster *c_ptr)
{
	u32 n_num;

	if (!c_ptr)
		return;
	for (n_num = 1; n_num <= c_ptr->highest_node; n_num++) {
		tipc_node_delete(c_ptr->nodes[n_num]);
	}
	for (n_num = LOWEST_SLAVE; n_num <= c_ptr->highest_slave; n_num++) {
		tipc_node_delete(c_ptr->nodes[n_num]);
	}
	kfree(c_ptr->nodes);
	kfree(c_ptr);
}