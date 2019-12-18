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

/* Variables and functions */
 int TIPC_CLUSTER_SCOPE ; 
 int TIPC_NODE_SCOPE ; 
 int TIPC_ZONE_SCOPE ; 
 scalar_t__ likely (int) ; 
 scalar_t__ tipc_cluster (int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int addr_scope(u32 domain)
{
	if (likely(!domain))
		return TIPC_ZONE_SCOPE;
	if (tipc_node(domain))
		return TIPC_NODE_SCOPE;
	if (tipc_cluster(domain))
		return TIPC_CLUSTER_SCOPE;
	return TIPC_ZONE_SCOPE;
}