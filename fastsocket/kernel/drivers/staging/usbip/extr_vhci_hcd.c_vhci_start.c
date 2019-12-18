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
struct vhci_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  seqnum; struct vhci_device* vdev; } ;
struct vhci_device {int rhport; } ;
struct usb_hcd {int uses_new_polling; int /*<<< orphan*/  state; scalar_t__ power_budget; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int VHCI_NPORTS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_group ; 
 struct vhci_hcd* hcd_to_vhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_hc (char*) ; 
 int /*<<< orphan*/  usbip_uerr (char*) ; 
 TYPE_1__* vhci_dev (struct vhci_hcd*) ; 
 int /*<<< orphan*/  vhci_device_init (struct vhci_device*) ; 

__attribute__((used)) static int vhci_start(struct usb_hcd *hcd)
{
	struct vhci_hcd *vhci = hcd_to_vhci(hcd);
	int rhport;
	int err = 0;

	usbip_dbg_vhci_hc("enter vhci_start\n");


	/* initialize private data of usb_hcd */

	for (rhport = 0; rhport < VHCI_NPORTS; rhport++) {
		struct vhci_device *vdev = &vhci->vdev[rhport];
		vhci_device_init(vdev);
		vdev->rhport = rhport;
	}

	atomic_set(&vhci->seqnum, 0);
	spin_lock_init(&vhci->lock);



	hcd->power_budget = 0; /* no limit */
	hcd->state  = HC_STATE_RUNNING;
	hcd->uses_new_polling = 1;


	/* vhci_hcd is now ready to be controlled through sysfs */
	err = sysfs_create_group(&vhci_dev(vhci)->kobj, &dev_attr_group);
	if (err) {
		usbip_uerr("create sysfs files\n");
		return err;
	}

	return 0;
}