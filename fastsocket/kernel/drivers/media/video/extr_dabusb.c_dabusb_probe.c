#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {size_t minor; TYPE_3__* altsetting; int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_9__ {int bNumConfigurations; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;
typedef  TYPE_4__* pdabusb_t ;
struct TYPE_12__ {size_t devnum; struct usb_device* usbdev; int /*<<< orphan*/  mutex; scalar_t__ remove_pending; } ;
struct TYPE_10__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_11__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  _DABUSB_IF ; 
 TYPE_4__* dabusb ; 
 int /*<<< orphan*/  dabusb_class ; 
 int /*<<< orphan*/  dabusb_fpga_download (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dabusb_loadmem (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_reset_configuration (struct usb_device*) ; 
 scalar_t__ usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,TYPE_4__*) ; 

__attribute__((used)) static int dabusb_probe (struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct usb_device *usbdev = interface_to_usbdev(intf);
	int retval;
	pdabusb_t s;

	dbg("dabusb: probe: vendor id 0x%x, device id 0x%x ifnum:%d",
	    le16_to_cpu(usbdev->descriptor.idVendor),
	    le16_to_cpu(usbdev->descriptor.idProduct),
	    intf->altsetting->desc.bInterfaceNumber);

	/* We don't handle multiple configurations */
	if (usbdev->descriptor.bNumConfigurations != 1)
		return -ENODEV;

	if (intf->altsetting->desc.bInterfaceNumber != _DABUSB_IF &&
	    le16_to_cpu(usbdev->descriptor.idProduct) == 0x9999)
		return -ENODEV;



	s = &dabusb[intf->minor];

	mutex_lock(&s->mutex);
	s->remove_pending = 0;
	s->usbdev = usbdev;
	s->devnum = intf->minor;

	if (usb_reset_configuration (usbdev) < 0) {
		dev_err(&intf->dev, "reset_configuration failed\n");
		goto reject;
	}
	if (le16_to_cpu(usbdev->descriptor.idProduct) == 0x2131) {
		dabusb_loadmem (s, NULL);
		goto reject;
	}
	else {
		dabusb_fpga_download (s, NULL);

		if (usb_set_interface (s->usbdev, _DABUSB_IF, 0) < 0) {
			dev_err(&intf->dev, "set_interface failed\n");
			goto reject;
		}
	}
	dbg("bound to interface: %d", intf->altsetting->desc.bInterfaceNumber);
	usb_set_intfdata (intf, s);
	mutex_unlock(&s->mutex);

	retval = usb_register_dev(intf, &dabusb_class);
	if (retval) {
		usb_set_intfdata (intf, NULL);
		return -ENOMEM;
	}

	return 0;

      reject:
	mutex_unlock(&s->mutex);
	s->usbdev = NULL;
	return -ENODEV;
}