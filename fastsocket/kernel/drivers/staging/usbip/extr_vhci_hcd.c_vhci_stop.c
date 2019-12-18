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
struct vhci_hcd {struct vhci_device* vdev; } ;
struct vhci_device {int /*<<< orphan*/  ud; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDEV_EVENT_REMOVED ; 
 int VHCI_NPORTS ; 
 int /*<<< orphan*/  dev_attr_group ; 
 struct vhci_hcd* hcd_to_vhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_hc (char*) ; 
 int /*<<< orphan*/  usbip_event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_stop_eh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_uinfo (char*) ; 
 TYPE_1__* vhci_dev (struct vhci_hcd*) ; 

__attribute__((used)) static void vhci_stop(struct usb_hcd *hcd)
{
	struct vhci_hcd *vhci = hcd_to_vhci(hcd);
	int rhport = 0;

	usbip_dbg_vhci_hc("stop VHCI controller\n");


	/* 1. remove the userland interface of vhci_hcd */
	sysfs_remove_group(&vhci_dev(vhci)->kobj, &dev_attr_group);

	/* 2. shutdown all the ports of vhci_hcd */
	for (rhport = 0 ; rhport < VHCI_NPORTS; rhport++) {
		struct vhci_device *vdev = &vhci->vdev[rhport];

		usbip_event_add(&vdev->ud, VDEV_EVENT_REMOVED);
		usbip_stop_eh(&vdev->ud);
	}


	usbip_uinfo("vhci_stop done\n");
}