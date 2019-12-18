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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_node {int dummy; } ;
struct cluster {struct tipc_node** nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_own_cluster (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_addr_domain_valid (int /*<<< orphan*/ ) ; 
 struct cluster* tipc_cltr_find (int /*<<< orphan*/ ) ; 
 struct tipc_node** tipc_local_nodes ; 
 size_t tipc_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct tipc_node *tipc_node_find(u32 addr)
{
	if (likely(in_own_cluster(addr)))
		return tipc_local_nodes[tipc_node(addr)];
	else if (tipc_addr_domain_valid(addr)) {
		struct cluster *c_ptr = tipc_cltr_find(addr);

		if (c_ptr)
			return c_ptr->nodes[tipc_node(addr)];
	}
	return NULL;
}