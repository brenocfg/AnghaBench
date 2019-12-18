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
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct usb_serial_port {scalar_t__ write_urb; scalar_t__ read_urb; TYPE_1__ port; } ;
struct usb_serial {int num_ports; struct usb_serial_port** port; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int usb_serial_generic_write_start (struct usb_serial_port*) ; 
 int usb_submit_urb (scalar_t__,int /*<<< orphan*/ ) ; 

int usb_serial_generic_resume(struct usb_serial *serial)
{
	struct usb_serial_port *port;
	int i, c = 0, r;

	for (i = 0; i < serial->num_ports; i++) {
		port = serial->port[i];
		if (!port->port.count)
			continue;

		if (port->read_urb) {
			r = usb_submit_urb(port->read_urb, GFP_NOIO);
			if (r < 0)
				c++;
		}

		if (port->write_urb) {
			r = usb_serial_generic_write_start(port);
			if (r < 0)
				c++;
		}
	}

	return c ? -EIO : 0;
}