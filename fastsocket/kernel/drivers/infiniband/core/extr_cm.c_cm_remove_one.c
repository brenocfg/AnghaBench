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
struct ib_port_modify {int /*<<< orphan*/  clr_port_cap_mask; } ;
struct ib_device {int phys_port_cnt; } ;
struct cm_port {int /*<<< orphan*/  mad_agent; int /*<<< orphan*/  port_num; } ;
struct cm_device {int /*<<< orphan*/  device; struct cm_port** port; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PORT_CM_SUP ; 
 TYPE_1__ cm ; 
 int /*<<< orphan*/  cm_client ; 
 int /*<<< orphan*/  cm_remove_port_fs (struct cm_port*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct cm_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_modify_port (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_port_modify*) ; 
 int /*<<< orphan*/  ib_unregister_mad_agent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cm_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cm_remove_one(struct ib_device *ib_device)
{
	struct cm_device *cm_dev;
	struct cm_port *port;
	struct ib_port_modify port_modify = {
		.clr_port_cap_mask = IB_PORT_CM_SUP
	};
	unsigned long flags;
	int i;

	cm_dev = ib_get_client_data(ib_device, &cm_client);
	if (!cm_dev)
		return;

	write_lock_irqsave(&cm.device_lock, flags);
	list_del(&cm_dev->list);
	write_unlock_irqrestore(&cm.device_lock, flags);

	for (i = 1; i <= ib_device->phys_port_cnt; i++) {
		port = cm_dev->port[i-1];
		ib_modify_port(ib_device, port->port_num, 0, &port_modify);
		ib_unregister_mad_agent(port->mad_agent);
		flush_workqueue(cm.wq);
		cm_remove_port_fs(port);
	}
	device_unregister(cm_dev->device);
	kfree(cm_dev);
}