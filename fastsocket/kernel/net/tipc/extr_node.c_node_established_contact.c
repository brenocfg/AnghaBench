#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ supported; int /*<<< orphan*/  acked; } ;
struct tipc_node {int /*<<< orphan*/  addr; TYPE_1__ bclink; struct cluster* owner; } ;
struct cluster {int dummy; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 int LOWEST_SLAVE ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ in_own_cluster (int /*<<< orphan*/ ) ; 
 scalar_t__ is_slave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_bclink_get_last_sent () ; 
 int /*<<< orphan*/  tipc_cltr_bcast_new_route (struct cluster*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cltr_bcast_nodes ; 
 struct cluster* tipc_cltr_create (int /*<<< orphan*/ ) ; 
 struct cluster* tipc_cltr_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cltr_send_local_routes (struct cluster*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cltr_send_slave_routes (struct cluster*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_highest_allowed_slave ; 
 int /*<<< orphan*/  tipc_k_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_max_nodes ; 
 scalar_t__ tipc_named_node_up ; 
 int /*<<< orphan*/  tipc_net_send_external_routes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_has_active_routes (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 int /*<<< orphan*/  tipc_own_tag ; 

__attribute__((used)) static void node_established_contact(struct tipc_node *n_ptr)
{
	struct cluster *c_ptr;

	dbg("node_established_contact:-> %x\n", n_ptr->addr);
	if (!tipc_node_has_active_routes(n_ptr) && in_own_cluster(n_ptr->addr)) {
		tipc_k_signal((Handler)tipc_named_node_up, n_ptr->addr);
	}

	/* Syncronize broadcast acks */
	n_ptr->bclink.acked = tipc_bclink_get_last_sent();

	if (is_slave(tipc_own_addr))
		return;
	if (!in_own_cluster(n_ptr->addr)) {
		/* Usage case 1 (see above) */
		c_ptr = tipc_cltr_find(tipc_own_addr);
		if (!c_ptr)
			c_ptr = tipc_cltr_create(tipc_own_addr);
		if (c_ptr)
			tipc_cltr_bcast_new_route(c_ptr, n_ptr->addr, 1,
						  tipc_max_nodes);
		return;
	}

	c_ptr = n_ptr->owner;
	if (is_slave(n_ptr->addr)) {
		/* Usage case 2 (see above) */
		tipc_cltr_bcast_new_route(c_ptr, n_ptr->addr, 1, tipc_max_nodes);
		tipc_cltr_send_local_routes(c_ptr, n_ptr->addr);
		return;
	}

	if (n_ptr->bclink.supported) {
		tipc_nmap_add(&tipc_cltr_bcast_nodes, n_ptr->addr);
		if (n_ptr->addr < tipc_own_addr)
			tipc_own_tag++;
	}

	/* Case 3 (see above) */
	tipc_net_send_external_routes(n_ptr->addr);
	tipc_cltr_send_slave_routes(c_ptr, n_ptr->addr);
	tipc_cltr_bcast_new_route(c_ptr, n_ptr->addr, LOWEST_SLAVE,
				  tipc_highest_allowed_slave);
}