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
struct usb_tranzport {struct usb_tranzport* interrupt_out_buffer; struct usb_tranzport* interrupt_in_buffer; struct usb_tranzport* ring_buffer; int /*<<< orphan*/  interrupt_out_urb; int /*<<< orphan*/  interrupt_in_urb; TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_compress_wheel ; 
 int /*<<< orphan*/  dev_attr_enable ; 
 int /*<<< orphan*/  dev_attr_offline ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct usb_tranzport*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_tranzport_abort_transfers (struct usb_tranzport*) ; 

__attribute__((used)) static void usb_tranzport_delete(struct usb_tranzport *dev)
{
	usb_tranzport_abort_transfers(dev);
	if (dev->intf != NULL) {
		device_remove_file(&dev->intf->dev, &dev_attr_enable);
		device_remove_file(&dev->intf->dev, &dev_attr_offline);
		device_remove_file(&dev->intf->dev, &dev_attr_compress_wheel);
	}

	/* free data structures */
	usb_free_urb(dev->interrupt_in_urb);
	usb_free_urb(dev->interrupt_out_urb);
	kfree(dev->ring_buffer);
	kfree(dev->interrupt_in_buffer);
	kfree(dev->interrupt_out_buffer);
	kfree(dev);
}