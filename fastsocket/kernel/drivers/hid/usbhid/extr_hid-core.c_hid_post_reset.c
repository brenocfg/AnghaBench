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
struct usbhid_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  iofl; } ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct usb_device {int dummy; } ;
struct hid_device {struct usbhid_device* driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_RESET_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_io_error (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_idle (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hid_start_in (struct hid_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct hid_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbhid_restart_queues (struct usbhid_device*) ; 

__attribute__((used)) static int hid_post_reset(struct usb_interface *intf)
{
	struct usb_device *dev = interface_to_usbdev (intf);
	struct hid_device *hid = usb_get_intfdata(intf);
	struct usbhid_device *usbhid = hid->driver_data;
	int status;

	spin_lock_irq(&usbhid->lock);
	clear_bit(HID_RESET_PENDING, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);
	hid_set_idle(dev, intf->cur_altsetting->desc.bInterfaceNumber, 0, 0);
	status = hid_start_in(hid);
	if (status < 0)
		hid_io_error(hid);
	usbhid_restart_queues(usbhid);

	return 0;
}