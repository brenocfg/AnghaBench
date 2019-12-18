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
struct port {int guest_connected; int /*<<< orphan*/  kref; int /*<<< orphan*/  outvq_lock; int /*<<< orphan*/  inbuf_lock; } ;
struct inode {struct cdev* i_cdev; } ;
struct file {struct port* private_data; } ;
struct cdev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  VIRTIO_CONSOLE_PORT_OPEN ; 
 struct port* find_port_by_devt (int /*<<< orphan*/ ) ; 
 scalar_t__ is_console_port (struct port*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  reclaim_consumed_buffers (struct port*) ; 
 int /*<<< orphan*/  remove_port ; 
 int /*<<< orphan*/  send_control_msg (struct port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int port_fops_open(struct inode *inode, struct file *filp)
{
	struct cdev *cdev = inode->i_cdev;
	struct port *port;
	int ret;

	/* We get the port with a kref here */
	port = find_port_by_devt(cdev->dev);
	if (!port) {
		/* Port was unplugged before we could proceed */
		return -ENXIO;
	}
	filp->private_data = port;

	/*
	 * Don't allow opening of console port devices -- that's done
	 * via /dev/hvc
	 */
	if (is_console_port(port)) {
		ret = -ENXIO;
		goto out;
	}

	/* Allow only one process to open a particular port at a time */
	spin_lock_irq(&port->inbuf_lock);
	if (port->guest_connected) {
		spin_unlock_irq(&port->inbuf_lock);
		ret = -EBUSY;
		goto out;
	}

	port->guest_connected = true;
	spin_unlock_irq(&port->inbuf_lock);

	spin_lock_irq(&port->outvq_lock);
	/*
	 * There might be a chance that we missed reclaiming a few
	 * buffers in the window of the port getting previously closed
	 * and opening now.
	 */
	reclaim_consumed_buffers(port);
	spin_unlock_irq(&port->outvq_lock);

	nonseekable_open(inode, filp);

	/* Notify host of port being opened */
	send_control_msg(filp->private_data, VIRTIO_CONSOLE_PORT_OPEN, 1);

	return 0;
out:
	kref_put(&port->kref, remove_port);
	return ret;
}