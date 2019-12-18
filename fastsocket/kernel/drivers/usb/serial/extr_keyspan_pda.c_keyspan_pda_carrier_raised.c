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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 scalar_t__ keyspan_pda_get_modem_info (struct usb_serial*,unsigned char*) ; 

__attribute__((used)) static int keyspan_pda_carrier_raised(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	unsigned char modembits;

	/* If we can read the modem status and the DCD is low then
	   carrier is not raised yet */
	if (keyspan_pda_get_modem_info(serial, &modembits) >= 0) {
		if (!(modembits & (1>>6)))
			return 0;
	}
	/* Carrier raised, or we failed (eg disconnected) so
	   progress accordingly */
	return 1;
}