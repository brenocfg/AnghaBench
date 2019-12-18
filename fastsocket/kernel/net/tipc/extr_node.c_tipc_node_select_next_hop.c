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
struct tipc_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ in_own_cluster (scalar_t__) ; 
 scalar_t__ is_slave (scalar_t__) ; 
 scalar_t__ tipc_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_addr_domain_valid (scalar_t__) ; 
 int /*<<< orphan*/  tipc_cluster (scalar_t__) ; 
 struct tipc_node* tipc_net_select_remote_node (scalar_t__,scalar_t__) ; 
 scalar_t__ tipc_net_select_router (scalar_t__,scalar_t__) ; 
 struct tipc_node* tipc_node_find (scalar_t__) ; 
 scalar_t__ tipc_node_has_active_links (struct tipc_node*) ; 
 struct tipc_node* tipc_node_select (scalar_t__,scalar_t__) ; 
 scalar_t__ tipc_node_select_router (struct tipc_node*,scalar_t__) ; 
 int /*<<< orphan*/  tipc_zone (scalar_t__) ; 

struct tipc_node *tipc_node_select_next_hop(u32 addr, u32 selector)
{
	struct tipc_node *n_ptr;
	u32 router_addr;

	if (!tipc_addr_domain_valid(addr))
		return NULL;

	/* Look for direct link to destination processsor */
	n_ptr = tipc_node_find(addr);
	if (n_ptr && tipc_node_has_active_links(n_ptr))
		return n_ptr;

	/* Cluster local system nodes *must* have direct links */
	if (!is_slave(addr) && in_own_cluster(addr))
		return NULL;

	/* Look for cluster local router with direct link to node */
	router_addr = tipc_node_select_router(n_ptr, selector);
	if (router_addr)
		return tipc_node_select(router_addr, selector);

	/* Slave nodes can only be accessed within own cluster via a
	   known router with direct link -- if no router was found,give up */
	if (is_slave(addr))
		return NULL;

	/* Inter zone/cluster -- find any direct link to remote cluster */
	addr = tipc_addr(tipc_zone(addr), tipc_cluster(addr), 0);
	n_ptr = tipc_net_select_remote_node(addr, selector);
	if (n_ptr && tipc_node_has_active_links(n_ptr))
		return n_ptr;

	/* Last resort -- look for any router to anywhere in remote zone */
	router_addr =  tipc_net_select_router(addr, selector);
	if (router_addr)
		return tipc_node_select(router_addr, selector);

	return NULL;
}