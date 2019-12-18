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
struct TYPE_2__ {scalar_t__ count; } ;
struct usb_serial_port {int /*<<< orphan*/  mutex; TYPE_1__ port; } ;
struct usb_serial {struct usb_serial_port** port; } ;
struct usb_interface {int dummy; } ;
struct opticon_private {int /*<<< orphan*/  bulk_read_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usb_serial* usb_get_intfdata (struct usb_interface*) ; 
 struct opticon_private* usb_get_serial_data (struct usb_serial*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opticon_resume(struct usb_interface *intf)
{
	struct usb_serial *serial = usb_get_intfdata(intf);
	struct opticon_private *priv = usb_get_serial_data(serial);
	struct usb_serial_port *port = serial->port[0];
	int result;

	mutex_lock(&port->mutex);
	if (port->port.count)
		result = usb_submit_urb(priv->bulk_read_urb, GFP_NOIO);
	else
		result = 0;
	mutex_unlock(&port->mutex);
	return result;
}