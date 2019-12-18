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
typedef  enum rdma_transport_type { ____Placeholder_rdma_transport_type } rdma_transport_type ;
typedef  enum rdma_node_type { ____Placeholder_rdma_node_type } rdma_node_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RDMA_NODE_IB_CA 131 
#define  RDMA_NODE_IB_ROUTER 130 
#define  RDMA_NODE_IB_SWITCH 129 
#define  RDMA_NODE_RNIC 128 
 int RDMA_TRANSPORT_IB ; 
 int RDMA_TRANSPORT_IWARP ; 

enum rdma_transport_type
rdma_node_get_transport(enum rdma_node_type node_type)
{
	switch (node_type) {
	case RDMA_NODE_IB_CA:
	case RDMA_NODE_IB_SWITCH:
	case RDMA_NODE_IB_ROUTER:
		return RDMA_TRANSPORT_IB;
	case RDMA_NODE_RNIC:
		return RDMA_TRANSPORT_IWARP;
	default:
		BUG();
		return 0;
	}
}