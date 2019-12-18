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
struct ib_sa_port {int dummy; } ;
struct ib_sa_device {int start_port; int end_port; TYPE_1__* port; int /*<<< orphan*/  event_handler; } ;
struct ib_device {scalar_t__ node_type; int phys_port_cnt; } ;
struct TYPE_2__ {int port_num; int /*<<< orphan*/  agent; int /*<<< orphan*/  update_task; int /*<<< orphan*/ * sm_ah; int /*<<< orphan*/  ah_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 int /*<<< orphan*/  INIT_IB_EVENT_HANDLER (int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ RDMA_NODE_IB_SWITCH ; 
 scalar_t__ RDMA_TRANSPORT_IB ; 
 scalar_t__ ib_register_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_register_mad_agent (struct ib_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_sa_device*) ; 
 int /*<<< orphan*/  ib_sa_event ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct ib_sa_device*) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_sa_device*) ; 
 struct ib_sa_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_node_get_transport (scalar_t__) ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int) ; 
 int /*<<< orphan*/  recv_handler ; 
 int /*<<< orphan*/  sa_client ; 
 int /*<<< orphan*/  send_handler ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_sm_ah (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_sa_add_one(struct ib_device *device)
{
	struct ib_sa_device *sa_dev;
	int s, e, i;

	if (rdma_node_get_transport(device->node_type) != RDMA_TRANSPORT_IB)
		return;

	if (device->node_type == RDMA_NODE_IB_SWITCH)
		s = e = 0;
	else {
		s = 1;
		e = device->phys_port_cnt;
	}

	sa_dev = kzalloc(sizeof *sa_dev +
			 (e - s + 1) * sizeof (struct ib_sa_port),
			 GFP_KERNEL);
	if (!sa_dev)
		return;

	sa_dev->start_port = s;
	sa_dev->end_port   = e;

	for (i = 0; i <= e - s; ++i) {
		spin_lock_init(&sa_dev->port[i].ah_lock);
		if (rdma_port_get_link_layer(device, i + 1) != IB_LINK_LAYER_INFINIBAND)
			continue;

		sa_dev->port[i].sm_ah    = NULL;
		sa_dev->port[i].port_num = i + s;

		sa_dev->port[i].agent =
			ib_register_mad_agent(device, i + s, IB_QPT_GSI,
					      NULL, 0, send_handler,
					      recv_handler, sa_dev);
		if (IS_ERR(sa_dev->port[i].agent))
			goto err;

		INIT_WORK(&sa_dev->port[i].update_task, update_sm_ah);
	}

	ib_set_client_data(device, &sa_client, sa_dev);

	/*
	 * We register our event handler after everything is set up,
	 * and then update our cached info after the event handler is
	 * registered to avoid any problems if a port changes state
	 * during our initialization.
	 */

	INIT_IB_EVENT_HANDLER(&sa_dev->event_handler, device, ib_sa_event);
	if (ib_register_event_handler(&sa_dev->event_handler))
		goto err;

	for (i = 0; i <= e - s; ++i)
		if (rdma_port_get_link_layer(device, i + 1) == IB_LINK_LAYER_INFINIBAND)
			update_sm_ah(&sa_dev->port[i].update_task);

	return;

err:
	while (--i >= 0)
		if (rdma_port_get_link_layer(device, i + 1) == IB_LINK_LAYER_INFINIBAND)
			ib_unregister_mad_agent(sa_dev->port[i].agent);

	kfree(sa_dev);

	return;
}