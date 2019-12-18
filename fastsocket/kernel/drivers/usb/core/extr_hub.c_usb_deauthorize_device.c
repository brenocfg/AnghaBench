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
struct TYPE_2__ {scalar_t__ bNumConfigurations; } ;
struct usb_device {scalar_t__ authorized; TYPE_1__ descriptor; void* serial; void* manufacturer; void* product; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_destroy_configuration (struct usb_device*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_configuration (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

int usb_deauthorize_device(struct usb_device *usb_dev)
{
	usb_lock_device(usb_dev);
	if (usb_dev->authorized == 0)
		goto out_unauthorized;

	usb_dev->authorized = 0;
	usb_set_configuration(usb_dev, -1);

	kfree(usb_dev->product);
	usb_dev->product = kstrdup("n/a (unauthorized)", GFP_KERNEL);
	kfree(usb_dev->manufacturer);
	usb_dev->manufacturer = kstrdup("n/a (unauthorized)", GFP_KERNEL);
	kfree(usb_dev->serial);
	usb_dev->serial = kstrdup("n/a (unauthorized)", GFP_KERNEL);

	usb_destroy_configuration(usb_dev);
	usb_dev->descriptor.bNumConfigurations = 0;

out_unauthorized:
	usb_unlock_device(usb_dev);
	return 0;
}