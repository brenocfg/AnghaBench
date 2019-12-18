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
typedef  int u8 ;
struct ib_port_modify {scalar_t__ clr_port_cap_mask; scalar_t__ set_port_cap_mask; } ;
struct ib_mad_reg_req {int /*<<< orphan*/  method_mask; int /*<<< orphan*/  mgmt_class_version; int /*<<< orphan*/  mgmt_class; } ;
struct ib_device {int phys_port_cnt; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  node_type; } ;
struct cm_port {int port_num; int /*<<< orphan*/  mad_agent; struct cm_device* cm_dev; } ;
struct cm_device {int /*<<< orphan*/  device; struct cm_port** port; int /*<<< orphan*/  list; struct ib_device* ib_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  device_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_CM_CLASS_VERSION ; 
 int /*<<< orphan*/  IB_MGMT_CLASS_CM ; 
 int /*<<< orphan*/  IB_MGMT_METHOD_SEND ; 
 scalar_t__ IB_PORT_CM_SUP ; 
 int /*<<< orphan*/  IB_QPT_GSI ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RDMA_TRANSPORT_IB ; 
 TYPE_1__ cm ; 
 int /*<<< orphan*/  cm_class ; 
 int /*<<< orphan*/  cm_client ; 
 int cm_create_port_fs (struct cm_port*) ; 
 int /*<<< orphan*/  cm_get_ack_delay (struct cm_device*) ; 
 int /*<<< orphan*/  cm_recv_handler ; 
 int /*<<< orphan*/  cm_remove_port_fs (struct cm_port*) ; 
 int /*<<< orphan*/  cm_send_handler ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int ib_modify_port (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_port_modify*) ; 
 int /*<<< orphan*/  ib_register_mad_agent (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_mad_reg_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cm_port*) ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct cm_device*) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cm_device*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_node_get_transport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cm_add_one(struct ib_device *ib_device)
{
	struct cm_device *cm_dev;
	struct cm_port *port;
	struct ib_mad_reg_req reg_req = {
		.mgmt_class = IB_MGMT_CLASS_CM,
		.mgmt_class_version = IB_CM_CLASS_VERSION
	};
	struct ib_port_modify port_modify = {
		.set_port_cap_mask = IB_PORT_CM_SUP
	};
	unsigned long flags;
	int ret;
	u8 i;

	if (rdma_node_get_transport(ib_device->node_type) != RDMA_TRANSPORT_IB)
		return;

	cm_dev = kzalloc(sizeof(*cm_dev) + sizeof(*port) *
			 ib_device->phys_port_cnt, GFP_KERNEL);
	if (!cm_dev)
		return;

	cm_dev->ib_device = ib_device;
	cm_get_ack_delay(cm_dev);

	cm_dev->device = device_create(&cm_class, &ib_device->dev,
				       MKDEV(0, 0), NULL,
				       "%s", ib_device->name);
	if (IS_ERR(cm_dev->device)) {
		kfree(cm_dev);
		return;
	}

	set_bit(IB_MGMT_METHOD_SEND, reg_req.method_mask);
	for (i = 1; i <= ib_device->phys_port_cnt; i++) {
		port = kzalloc(sizeof *port, GFP_KERNEL);
		if (!port)
			goto error1;

		cm_dev->port[i-1] = port;
		port->cm_dev = cm_dev;
		port->port_num = i;

		ret = cm_create_port_fs(port);
		if (ret)
			goto error1;

		port->mad_agent = ib_register_mad_agent(ib_device, i,
							IB_QPT_GSI,
							&reg_req,
							0,
							cm_send_handler,
							cm_recv_handler,
							port);
		if (IS_ERR(port->mad_agent))
			goto error2;

		ret = ib_modify_port(ib_device, i, 0, &port_modify);
		if (ret)
			goto error3;
	}
	ib_set_client_data(ib_device, &cm_client, cm_dev);

	write_lock_irqsave(&cm.device_lock, flags);
	list_add_tail(&cm_dev->list, &cm.device_list);
	write_unlock_irqrestore(&cm.device_lock, flags);
	return;

error3:
	ib_unregister_mad_agent(port->mad_agent);
error2:
	cm_remove_port_fs(port);
error1:
	port_modify.set_port_cap_mask = 0;
	port_modify.clr_port_cap_mask = IB_PORT_CM_SUP;
	while (--i) {
		port = cm_dev->port[i-1];
		ib_modify_port(ib_device, port->port_num, 0, &port_modify);
		ib_unregister_mad_agent(port->mad_agent);
		cm_remove_port_fs(port);
	}
	device_unregister(cm_dev->device);
	kfree(cm_dev);
}