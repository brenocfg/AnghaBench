#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_line6 {TYPE_4__* properties; struct usb_device* usbdev; int /*<<< orphan*/  ifcdev; int /*<<< orphan*/ * urb_listen; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct usb_interface {TYPE_5__ dev; TYPE_2__* cur_altsetting; } ;
struct TYPE_8__ {int idProduct; } ;
struct usb_device {TYPE_3__ descriptor; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int bInterfaceNumber; } ;
struct TYPE_7__ {TYPE_1__ desc; } ;

/* Variables and functions */
#define  LINE6_DEVID_BASSPODXT 143 
#define  LINE6_DEVID_BASSPODXTLIVE 142 
#define  LINE6_DEVID_BASSPODXTPRO 141 
#define  LINE6_DEVID_GUITARPORT 140 
#define  LINE6_DEVID_POCKETPOD 139 
#define  LINE6_DEVID_PODX3 138 
#define  LINE6_DEVID_PODX3LIVE 137 
#define  LINE6_DEVID_PODXT 136 
#define  LINE6_DEVID_PODXTLIVE 135 
#define  LINE6_DEVID_PODXTPRO 134 
#define  LINE6_DEVID_TONEPORT_GX 133 
#define  LINE6_DEVID_TONEPORT_UX1 132 
#define  LINE6_DEVID_TONEPORT_UX2 131 
#define  LINE6_DEVID_VARIAX 130 
 int LINE6_MAX_DEVICES ; 
 int /*<<< orphan*/  MISSING_CASE ; 
#define  PODXTLIVE_INTERFACE_POD 129 
#define  PODXTLIVE_INTERFACE_VARIAX 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  line6_destruct (struct usb_interface*) ; 
 struct usb_line6** line6_devices ; 
 int /*<<< orphan*/  line6_list_devices () ; 
 int /*<<< orphan*/  pod_disconnect (struct usb_interface*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  toneport_disconnect (struct usb_interface*) ; 
 struct usb_line6* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  variax_disconnect (struct usb_interface*) ; 

__attribute__((used)) static void line6_disconnect(struct usb_interface *interface)
{
	struct usb_line6 *line6;
	struct usb_device *usbdev;
	int interface_number, i;

	if (interface == NULL)
		return;
	usbdev = interface_to_usbdev(interface);
	if (usbdev == NULL)
		return;

	sysfs_remove_link(&interface->dev.kobj, "usb_device");

	interface_number = interface->cur_altsetting->desc.bInterfaceNumber;
	line6 = usb_get_intfdata(interface);

	if (line6 != NULL) {
		if (line6->urb_listen != NULL)
			usb_kill_urb(line6->urb_listen);

		if (usbdev != line6->usbdev)
			dev_err(line6->ifcdev,
				"driver bug: inconsistent usb device\n");

		switch (line6->usbdev->descriptor.idProduct) {
		case LINE6_DEVID_BASSPODXT:
		case LINE6_DEVID_BASSPODXTLIVE:
		case LINE6_DEVID_BASSPODXTPRO:
		case LINE6_DEVID_POCKETPOD:
		case LINE6_DEVID_PODX3:
		case LINE6_DEVID_PODX3LIVE:
		case LINE6_DEVID_PODXT:
		case LINE6_DEVID_PODXTPRO:
			pod_disconnect(interface);
			break;

		case LINE6_DEVID_PODXTLIVE:
			switch (interface_number) {
			case PODXTLIVE_INTERFACE_POD:
				pod_disconnect(interface);
				break;

			case PODXTLIVE_INTERFACE_VARIAX:
				variax_disconnect(interface);
				break;
			}

			break;

		case LINE6_DEVID_VARIAX:
			variax_disconnect(interface);
			break;

		case LINE6_DEVID_TONEPORT_GX:
		case LINE6_DEVID_TONEPORT_UX1:
		case LINE6_DEVID_TONEPORT_UX2:
		case LINE6_DEVID_GUITARPORT:
			toneport_disconnect(interface);
			break;

		default:
			MISSING_CASE;
		}

		dev_info(&interface->dev, "Line6 %s now disconnected\n", line6->properties->name);

		for (i = LINE6_MAX_DEVICES; i--;)
			if (line6_devices[i] == line6)
				line6_devices[i] = NULL;
	}

	line6_destruct(interface);

	/* decrement reference counters: */
	usb_put_intf(interface);
	usb_put_dev(usbdev);

	line6_list_devices();
}