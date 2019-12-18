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
struct mcast_port {int /*<<< orphan*/  comp; } ;
struct mcast_device {int end_port; int start_port; struct mcast_port* port; int /*<<< orphan*/  event_handler; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int /*<<< orphan*/  deref_port (struct mcast_port*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct mcast_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mcast_device*) ; 
 int /*<<< orphan*/  mcast_client ; 
 int /*<<< orphan*/  mcast_wq ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcast_remove_one(struct ib_device *device)
{
	struct mcast_device *dev;
	struct mcast_port *port;
	int i;

	dev = ib_get_client_data(device, &mcast_client);
	if (!dev)
		return;

	ib_unregister_event_handler(&dev->event_handler);
	flush_workqueue(mcast_wq);

	for (i = 0; i <= dev->end_port - dev->start_port; i++) {
		if (rdma_port_get_link_layer(device, dev->start_port + i) ==
		    IB_LINK_LAYER_INFINIBAND) {
			port = &dev->port[i];
			deref_port(port);
			wait_for_completion(&port->comp);
		}
	}

	kfree(dev);
}