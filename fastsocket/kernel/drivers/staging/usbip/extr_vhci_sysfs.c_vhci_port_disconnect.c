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
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  lock; } ;
struct vhci_device {TYPE_1__ ud; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VDEV_EVENT_DOWN ; 
 scalar_t__ VDEV_ST_NULL ; 
 struct vhci_device* port_to_vdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* the_controller ; 
 int /*<<< orphan*/  usbip_dbg_vhci_sysfs (char*) ; 
 int /*<<< orphan*/  usbip_event_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_uerr (char*,scalar_t__) ; 

__attribute__((used)) static int vhci_port_disconnect(__u32 rhport)
{
	struct vhci_device *vdev;

	usbip_dbg_vhci_sysfs("enter\n");

	/* lock */
	spin_lock(&the_controller->lock);

	vdev = port_to_vdev(rhport);

	spin_lock(&vdev->ud.lock);
	if (vdev->ud.status == VDEV_ST_NULL) {
		usbip_uerr("not connected %d\n", vdev->ud.status);

		/* unlock */
		spin_unlock(&vdev->ud.lock);
		spin_unlock(&the_controller->lock);

		return -EINVAL;
	}

	/* unlock */
	spin_unlock(&vdev->ud.lock);
	spin_unlock(&the_controller->lock);

	usbip_event_add(&vdev->ud, VDEV_EVENT_DOWN);

	return 0;
}