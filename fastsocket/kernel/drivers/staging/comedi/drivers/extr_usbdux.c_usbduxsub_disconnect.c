#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usbduxsub {int /*<<< orphan*/  sem; struct usb_device* usbdev; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_usb_auto_unconfig (struct usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  start_stop_sem ; 
 int /*<<< orphan*/  tidy_up (struct usbduxsub*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 struct usbduxsub* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void usbduxsub_disconnect(struct usb_interface *intf)
{
	struct usbduxsub *usbduxsub_tmp = usb_get_intfdata(intf);
	struct usb_device *udev = interface_to_usbdev(intf);

	if (!usbduxsub_tmp) {
		dev_err(&intf->dev,
			"comedi_: disconnect called with null pointer.\n");
		return;
	}
	if (usbduxsub_tmp->usbdev != udev) {
		dev_err(&intf->dev, "comedi_: BUG! called with wrong ptr!!!\n");
		return;
	}
	comedi_usb_auto_unconfig(udev);
	down(&start_stop_sem);
	down(&usbduxsub_tmp->sem);
	tidy_up(usbduxsub_tmp);
	up(&usbduxsub_tmp->sem);
	up(&start_stop_sem);
	dev_dbg(&intf->dev, "comedi_: disconnected from the usb\n");
}