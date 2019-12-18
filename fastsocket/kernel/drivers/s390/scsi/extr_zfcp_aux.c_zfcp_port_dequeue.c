#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct zfcp_port {TYPE_2__ sysfs_device; int /*<<< orphan*/  adapter; int /*<<< orphan*/  refcount; int /*<<< orphan*/  remove_wq; int /*<<< orphan*/  test_link_work; int /*<<< orphan*/  rport_work; int /*<<< orphan*/  gid_pn_work; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int /*<<< orphan*/  config_lock; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_adapter_put (int /*<<< orphan*/ ) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_port_put (struct zfcp_port*) ; 
 int /*<<< orphan*/  zfcp_sysfs_port_attrs ; 

void zfcp_port_dequeue(struct zfcp_port *port)
{
	write_lock_irq(&zfcp_data.config_lock);
	list_del(&port->list);
	write_unlock_irq(&zfcp_data.config_lock);
	if (cancel_work_sync(&port->gid_pn_work))
		zfcp_port_put(port);
	if (cancel_work_sync(&port->rport_work))
		zfcp_port_put(port);
	if (cancel_work_sync(&port->test_link_work))
		zfcp_port_put(port);
	wait_event(port->remove_wq, atomic_read(&port->refcount) == 0);
	zfcp_adapter_put(port->adapter);
	sysfs_remove_group(&port->sysfs_device.kobj, &zfcp_sysfs_port_attrs);
	device_unregister(&port->sysfs_device);
}