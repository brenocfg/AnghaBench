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
struct usb_serial_port {int dummy; } ;

/* Variables and functions */
 unsigned int CONTROL_DCD ; 
 int /*<<< orphan*/  CP210X_GET_MDMSTS ; 
 int /*<<< orphan*/  cp210x_get_config (struct usb_serial_port*,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int cp210x_carrier_raised(struct usb_serial_port *p)
{
	unsigned int control;
	cp210x_get_config(p, CP210X_GET_MDMSTS, &control, 1);
	if (control & CONTROL_DCD)
		return 1;
	return 0;
}