#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  tcp_socket; } ;
struct vhci_device {int speed; int devid; TYPE_2__ ud; TYPE_1__* udev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ VDEV_ST_USED ; 
 int VHCI_NPORTS ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 struct vhci_device* port_to_vdev (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 TYPE_3__* the_controller ; 

__attribute__((used)) static ssize_t show_status(struct device *dev, struct device_attribute *attr,
			   char *out)
{
	char *s = out;
	int i = 0;

	BUG_ON(!the_controller || !out);

	spin_lock(&the_controller->lock);

	/*
	 * output example:
	 * prt sta spd dev socket           local_busid
	 * 000 004 000 000         c5a7bb80 1-2.3
	 * 001 004 000 000         d8cee980 2-3.4
	 *
	 * IP address can be retrieved from a socket pointer address by looking
	 * up /proc/net/{tcp,tcp6}. Also, a userland program may remember a
	 * port number and its peer IP address.
	 */
	out += sprintf(out, "prt sta spd bus dev socket           "
		       "local_busid\n");

	for (i = 0; i < VHCI_NPORTS; i++) {
		struct vhci_device *vdev = port_to_vdev(i);

		spin_lock(&vdev->ud.lock);

		out += sprintf(out, "%03u %03u ", i, vdev->ud.status);

		if (vdev->ud.status == VDEV_ST_USED) {
			out += sprintf(out, "%03u %08x ",
					vdev->speed, vdev->devid);
			out += sprintf(out, "%16p ", vdev->ud.tcp_socket);
			out += sprintf(out, "%s", dev_name(&vdev->udev->dev));

		} else
			out += sprintf(out, "000 000 000 0000000000000000 0-0");

		out += sprintf(out, "\n");

		spin_unlock(&vdev->ud.lock);
	}

	spin_unlock(&the_controller->lock);

	return out - s;
}