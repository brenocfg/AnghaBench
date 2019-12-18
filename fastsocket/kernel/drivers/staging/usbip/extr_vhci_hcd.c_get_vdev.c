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
struct vhci_device {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vdev; } ;
struct TYPE_3__ {struct usb_device* udev; } ;

/* Variables and functions */
 int VHCI_NPORTS ; 
 struct vhci_device* port_to_vdev (int) ; 
 TYPE_2__* the_controller ; 

__attribute__((used)) static struct vhci_device *get_vdev(struct usb_device *udev)
{
	int i;

	if (!udev)
		return NULL;

	for (i = 0; i < VHCI_NPORTS; i++)
		if (the_controller->vdev[i].udev == udev)
			return port_to_vdev(i);

	return NULL;
}