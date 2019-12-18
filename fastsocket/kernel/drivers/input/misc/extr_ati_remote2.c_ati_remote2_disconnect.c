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
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_4__ {scalar_t__ bInterfaceNumber; } ;
struct usb_host_interface {TYPE_1__ desc; } ;
struct ati_remote2 {int /*<<< orphan*/ * intf; TYPE_2__* udev; int /*<<< orphan*/  idev; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ati_remote2_attr_group ; 
 int /*<<< orphan*/  ati_remote2_driver ; 
 int /*<<< orphan*/  ati_remote2_urb_cleanup (struct ati_remote2*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ati_remote2*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ati_remote2* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ati_remote2_disconnect(struct usb_interface *interface)
{
	struct ati_remote2 *ar2;
	struct usb_host_interface *alt = interface->cur_altsetting;

	if (alt->desc.bInterfaceNumber)
		return;

	ar2 = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	input_unregister_device(ar2->idev);

	sysfs_remove_group(&ar2->udev->dev.kobj, &ati_remote2_attr_group);

	ati_remote2_urb_cleanup(ar2);

	usb_driver_release_interface(&ati_remote2_driver, ar2->intf[1]);

	kfree(ar2);
}