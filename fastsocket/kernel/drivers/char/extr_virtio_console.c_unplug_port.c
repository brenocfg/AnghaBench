#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hvc; int /*<<< orphan*/  list; } ;
struct port {int guest_connected; int host_connected; int /*<<< orphan*/  kref; int /*<<< orphan*/  name; int /*<<< orphan*/  debugfs_file; int /*<<< orphan*/  cdev; TYPE_3__* dev; TYPE_2__* portdev; TYPE_1__ cons; int /*<<< orphan*/  inbuf_lock; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  list; } ;
struct TYPE_8__ {int /*<<< orphan*/  class; } ;
struct TYPE_7__ {int /*<<< orphan*/  devt; int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {int /*<<< orphan*/  ports_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hvc_remove (int /*<<< orphan*/ ) ; 
 scalar_t__ is_console_port (struct port*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_4__ pdrvdata ; 
 int /*<<< orphan*/  pdrvdata_lock ; 
 int /*<<< orphan*/  port_attribute_group ; 
 int /*<<< orphan*/  remove_port ; 
 int /*<<< orphan*/  remove_port_data (struct port*) ; 
 int /*<<< orphan*/  send_sigio_to_port (struct port*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unplug_port(struct port *port)
{
	spin_lock_irq(&port->portdev->ports_lock);
	list_del(&port->list);
	spin_unlock_irq(&port->portdev->ports_lock);

	spin_lock_irq(&port->inbuf_lock);
	if (port->guest_connected) {
		/* Let the app know the port is going down. */
		send_sigio_to_port(port);

		/* Do this after sigio is actually sent */
		port->guest_connected = false;
		port->host_connected = false;

		wake_up_interruptible(&port->waitqueue);
	}
	spin_unlock_irq(&port->inbuf_lock);

	if (is_console_port(port)) {
		spin_lock_irq(&pdrvdata_lock);
		list_del(&port->cons.list);
		spin_unlock_irq(&pdrvdata_lock);
		hvc_remove(port->cons.hvc);
	}

	remove_port_data(port);

	/*
	 * We should just assume the device itself has gone off --
	 * else a close on an open port later will try to send out a
	 * control message.
	 */
	port->portdev = NULL;

	sysfs_remove_group(&port->dev->kobj, &port_attribute_group);
	device_destroy(pdrvdata.class, port->dev->devt);
	cdev_del(port->cdev);

	debugfs_remove(port->debugfs_file);
	kfree(port->name);

	/*
	 * Locks around here are not necessary - a port can't be
	 * opened after we removed the port struct from ports_list
	 * above.
	 */
	kref_put(&port->kref, remove_port);
}