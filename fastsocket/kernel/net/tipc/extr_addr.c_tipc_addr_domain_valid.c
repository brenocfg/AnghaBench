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

/* Variables and functions */
 scalar_t__ LOWEST_SLAVE ; 
 scalar_t__ is_slave (scalar_t__) ; 
 scalar_t__ tipc_cluster (scalar_t__) ; 
 scalar_t__ tipc_max_clusters ; 
 scalar_t__ tipc_max_nodes ; 
 scalar_t__ tipc_max_slaves ; 
 scalar_t__ tipc_max_zones ; 
 scalar_t__ tipc_node (scalar_t__) ; 
 scalar_t__ tipc_zone (scalar_t__) ; 

int tipc_addr_domain_valid(u32 addr)
{
	u32 n = tipc_node(addr);
	u32 c = tipc_cluster(addr);
	u32 z = tipc_zone(addr);
	u32 max_nodes = tipc_max_nodes;

	if (is_slave(addr))
		max_nodes = LOWEST_SLAVE + tipc_max_slaves;
	if (n > max_nodes)
		return 0;
	if (c > tipc_max_clusters)
		return 0;
	if (z > tipc_max_zones)
		return 0;

	if (n && (!z || !c))
		return 0;
	if (c && !z)
		return 0;
	return 1;
}