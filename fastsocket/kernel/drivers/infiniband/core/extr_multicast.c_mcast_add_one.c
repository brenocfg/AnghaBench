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
struct mcast_port {int port_num; int /*<<< orphan*/  refcount; int /*<<< orphan*/  comp; int /*<<< orphan*/  table; int /*<<< orphan*/  lock; struct mcast_device* dev; } ;
struct mcast_device {int start_port; int end_port; int /*<<< orphan*/  event_handler; struct ib_device* device; struct mcast_port* port; } ;
struct ib_device {scalar_t__ node_type; int phys_port_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 scalar_t__ RDMA_NODE_IB_SWITCH ; 
 scalar_t__ RDMA_TRANSPORT_IB ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ib_register_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct mcast_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mcast_device*) ; 
 struct mcast_device* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcast_client ; 
 int /*<<< orphan*/  mcast_event_handler ; 
 scalar_t__ rdma_node_get_transport (scalar_t__) ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcast_add_one(struct ib_device *device)
{
	struct mcast_device *dev;
	struct mcast_port *port;
	int i;
	int count = 0;

	if (rdma_node_get_transport(device->node_type) != RDMA_TRANSPORT_IB)
		return;

	dev = kmalloc(sizeof *dev + device->phys_port_cnt * sizeof *port,
		      GFP_KERNEL);
	if (!dev)
		return;

	if (device->node_type == RDMA_NODE_IB_SWITCH)
		dev->start_port = dev->end_port = 0;
	else {
		dev->start_port = 1;
		dev->end_port = device->phys_port_cnt;
	}

	for (i = 0; i <= dev->end_port - dev->start_port; i++) {
		if (rdma_port_get_link_layer(device, dev->start_port + i) !=
		    IB_LINK_LAYER_INFINIBAND)
			continue;
		port = &dev->port[i];
		port->dev = dev;
		port->port_num = dev->start_port + i;
		spin_lock_init(&port->lock);
		port->table = RB_ROOT;
		init_completion(&port->comp);
		atomic_set(&port->refcount, 1);
		++count;
	}

	if (!count) {
		kfree(dev);
		return;
	}

	dev->device = device;
	ib_set_client_data(device, &mcast_client, dev);

	INIT_IB_EVENT_HANDLER(&dev->event_handler, device, mcast_event_handler);
	ib_register_event_handler(&dev->event_handler);
}