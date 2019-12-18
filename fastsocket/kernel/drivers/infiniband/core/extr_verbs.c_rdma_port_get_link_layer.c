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
typedef  int /*<<< orphan*/  u8 ;
struct ib_device {int (* get_link_layer ) (struct ib_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  node_type; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int IB_LINK_LAYER_INFINIBAND ; 
 int IB_LINK_LAYER_UNSPECIFIED ; 
#define  RDMA_TRANSPORT_IB 129 
#define  RDMA_TRANSPORT_IWARP 128 
 int rdma_node_get_transport (int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_device*,int /*<<< orphan*/ ) ; 

enum rdma_link_layer rdma_port_get_link_layer(struct ib_device *device, u8 port_num)
{
	if (device->get_link_layer)
		return device->get_link_layer(device, port_num);

	switch (rdma_node_get_transport(device->node_type)) {
	case RDMA_TRANSPORT_IB:
		return IB_LINK_LAYER_INFINIBAND;
	case RDMA_TRANSPORT_IWARP:
		return IB_LINK_LAYER_ETHERNET;
	default:
		return IB_LINK_LAYER_UNSPECIFIED;
	}
}