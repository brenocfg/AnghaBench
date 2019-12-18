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
struct usb_serial {int dummy; } ;

/* Variables and functions */
 scalar_t__ usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int visor_calc_num_ports(struct usb_serial *serial)
{
	int num_ports = (int)(long)(usb_get_serial_data(serial));

	if (num_ports)
		usb_set_serial_data(serial, NULL);

	return num_ports;
}