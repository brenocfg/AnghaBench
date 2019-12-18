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
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {scalar_t__ speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  adapter_nr ; 
 scalar_t__ dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  lme2510_properties ; 
 int /*<<< orphan*/  lme2510c_properties ; 
 int /*<<< orphan*/  lme_firmware_switch (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_reset_configuration (struct usb_device*) ; 
 int usb_reset_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lme2510_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	int ret = 0;

	usb_reset_configuration(udev);

	usb_set_interface(udev, intf->cur_altsetting->desc.bInterfaceNumber, 1);

	if (udev->speed != USB_SPEED_HIGH) {
		ret = usb_reset_device(udev);
		info("DEV Failed to connect in HIGH SPEED mode");
		return -ENODEV;
	}

	lme_firmware_switch(udev, 0);

	if (0 == dvb_usb_device_init(intf, &lme2510_properties,
				     THIS_MODULE, NULL, adapter_nr)) {
		info("DEV registering device driver");
		return 0;
	}
	if (0 == dvb_usb_device_init(intf, &lme2510c_properties,
				     THIS_MODULE, NULL, adapter_nr)) {
		info("DEV registering device driver");
		return 0;
	}

	info("DEV lme2510 Error");
	return -ENODEV;

}