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
struct spcp8x5_private {int line_status; } ;

/* Variables and functions */
 int MSR_STATUS_LINE_DCD ; 
 struct spcp8x5_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int spcp8x5_carrier_raised(struct usb_serial_port *port)
{
	struct spcp8x5_private *priv = usb_get_serial_port_data(port);
	if (priv->line_status & MSR_STATUS_LINE_DCD)
		return 1;
	return 0;
}