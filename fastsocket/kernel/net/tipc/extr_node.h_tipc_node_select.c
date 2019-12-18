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

/* Variables and functions */
 int /*<<< orphan*/  in_own_cluster (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct tipc_node** tipc_local_nodes ; 
 size_t tipc_node (int /*<<< orphan*/ ) ; 
 struct tipc_node* tipc_node_select_next_hop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct tipc_node *tipc_node_select(u32 addr, u32 selector)
{
	if (likely(in_own_cluster(addr)))
		return tipc_local_nodes[tipc_node(addr)];
	return tipc_node_select_next_hop(addr, selector);
}