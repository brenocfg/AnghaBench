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
typedef  int u32 ;
struct cluster {int highest_node; int /*<<< orphan*/ * nodes; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  in_own_cluster (int /*<<< orphan*/ ) ; 
 int tipc_max_nodes ; 
 scalar_t__ tipc_node_is_up (int /*<<< orphan*/ ) ; 
 int tipc_node_select_router (int /*<<< orphan*/ ,int) ; 

u32 tipc_cltr_select_router(struct cluster *c_ptr, u32 ref)
{
	u32 n_num;
	u32 ulim = c_ptr->highest_node;
	u32 mask;
	u32 tstart;

	assert(!in_own_cluster(c_ptr->addr));
	if (!ulim)
		return 0;

	/* Start entry must be random */
	mask = tipc_max_nodes;
	while (mask > ulim)
		mask >>= 1;
	tstart = ref & mask;
	n_num = tstart;

	/* Lookup upwards with wrap-around */
	do {
		if (tipc_node_is_up(c_ptr->nodes[n_num]))
			break;
	} while (++n_num <= ulim);
	if (n_num > ulim) {
		n_num = 1;
		do {
			if (tipc_node_is_up(c_ptr->nodes[n_num]))
				break;
		} while (++n_num < tstart);
		if (n_num == tstart)
			return 0;
	}
	assert(n_num <= ulim);
	return tipc_node_select_router(c_ptr->nodes[n_num], ref);
}