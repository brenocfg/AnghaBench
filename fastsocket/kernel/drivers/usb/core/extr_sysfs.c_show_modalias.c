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
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_4__ {int bInterfaceClass; int bInterfaceSubClass; int bInterfaceProtocol; } ;
struct usb_host_interface {TYPE_2__ desc; } ;
struct TYPE_3__ {int bDeviceClass; int bDeviceSubClass; int bDeviceProtocol; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int,int,int,int) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 

__attribute__((used)) static ssize_t show_modalias(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct usb_interface *intf;
	struct usb_device *udev;
	struct usb_host_interface *alt;

	intf = to_usb_interface(dev);
	udev = interface_to_usbdev(intf);
	alt = intf->cur_altsetting;

	return sprintf(buf, "usb:v%04Xp%04Xd%04Xdc%02Xdsc%02Xdp%02X"
			"ic%02Xisc%02Xip%02X\n",
			le16_to_cpu(udev->descriptor.idVendor),
			le16_to_cpu(udev->descriptor.idProduct),
			le16_to_cpu(udev->descriptor.bcdDevice),
			udev->descriptor.bDeviceClass,
			udev->descriptor.bDeviceSubClass,
			udev->descriptor.bDeviceProtocol,
			alt->desc.bInterfaceClass,
			alt->desc.bInterfaceSubClass,
			alt->desc.bInterfaceProtocol);
}