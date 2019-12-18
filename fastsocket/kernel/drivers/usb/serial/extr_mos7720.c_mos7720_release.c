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
struct usb_serial {int num_ports; int /*<<< orphan*/ * port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_get_serial_port_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mos7720_release(struct usb_serial *serial)
{
	int i;

	/* free private structure allocated for serial port */
	for (i = 0; i < serial->num_ports; ++i)
		kfree(usb_get_serial_port_data(serial->port[i]));

	/* free private structure allocated for serial device */
	kfree(usb_get_serial_data(serial));
}