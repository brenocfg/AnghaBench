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

/* Variables and functions */
 int SVC_POOL_GLOBAL ; 
 int SVC_POOL_PERCPU ; 
 int SVC_POOL_PERNODE ; 
 unsigned int any_online_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_online_map ; 
 int nr_cpus_node (unsigned int) ; 
 int nr_online_nodes ; 

__attribute__((used)) static int
svc_pool_map_choose_mode(void)
{
	unsigned int node;

	if (nr_online_nodes > 1) {
		/*
		 * Actually have multiple NUMA nodes,
		 * so split pools on NUMA node boundaries
		 */
		return SVC_POOL_PERNODE;
	}

	node = any_online_node(node_online_map);
	if (nr_cpus_node(node) > 2) {
		/*
		 * Non-trivial SMP, or CONFIG_NUMA on
		 * non-NUMA hardware, e.g. with a generic
		 * x86_64 kernel on Xeons.  In this case we
		 * want to divide the pools on cpu boundaries.
		 */
		return SVC_POOL_PERCPU;
	}

	/* default: one global pool */
	return SVC_POOL_GLOBAL;
}