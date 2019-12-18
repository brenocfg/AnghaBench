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
struct tipc_node {scalar_t__* links; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 size_t MAX_BEARERS ; 
 int /*<<< orphan*/  TIPC_OUTPUT ; 
 int /*<<< orphan*/  addr_string_fill (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_print (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_link_reset (scalar_t__) ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 struct tipc_node* tipc_node_find (size_t) ; 
 int /*<<< orphan*/  tipc_node_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_unlock (struct tipc_node*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_reset_all(unsigned long addr)
{
	struct tipc_node *n_ptr;
	char addr_string[16];
	u32 i;

	read_lock_bh(&tipc_net_lock);
	n_ptr = tipc_node_find((u32)addr);
	if (!n_ptr) {
		read_unlock_bh(&tipc_net_lock);
		return;	/* node no longer exists */
	}

	tipc_node_lock(n_ptr);

	warn("Resetting all links to %s\n",
	     addr_string_fill(addr_string, n_ptr->addr));

	for (i = 0; i < MAX_BEARERS; i++) {
		if (n_ptr->links[i]) {
			link_print(n_ptr->links[i], TIPC_OUTPUT,
				   "Resetting link\n");
			tipc_link_reset(n_ptr->links[i]);
		}
	}

	tipc_node_unlock(n_ptr);
	read_unlock_bh(&tipc_net_lock);
}