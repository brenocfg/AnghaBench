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
struct usb_serial {int /*<<< orphan*/ * port; } ;
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct ch341_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ch341_configure (struct usb_device*,struct ch341_private*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct usb_serial* usb_get_intfdata (struct usb_interface*) ; 
 struct ch341_private* usb_get_serial_port_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_serial_resume (struct usb_interface*) ; 

__attribute__((used)) static int ch341_reset_resume(struct usb_interface *intf)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usb_serial *serial = NULL;
	struct ch341_private *priv;

	serial = usb_get_intfdata(intf);
	priv = usb_get_serial_port_data(serial->port[0]);

	/*reconfigure ch341 serial port after bus-reset*/
	ch341_configure(dev, priv);

	usb_serial_resume(intf);

	return 0;
}