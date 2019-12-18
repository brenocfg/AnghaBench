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
typedef  scalar_t__ u32 ;
struct tipc_node {int /*<<< orphan*/  addr; struct tipc_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_scope (scalar_t__ const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 scalar_t__ tipc_node_is_up (struct tipc_node*) ; 
 struct tipc_node* tipc_nodes ; 

u32 tipc_available_nodes(const u32 domain)
{
	struct tipc_node *n_ptr;
	u32 cnt = 0;

	read_lock_bh(&tipc_net_lock);
	for (n_ptr = tipc_nodes; n_ptr; n_ptr = n_ptr->next) {
		if (!in_scope(domain, n_ptr->addr))
			continue;
		if (tipc_node_is_up(n_ptr))
			cnt++;
	}
	read_unlock_bh(&tipc_net_lock);
	return cnt;
}