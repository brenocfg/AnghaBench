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
struct quatech2_port {int xmit_flush; } ;

/* Variables and functions */
 struct quatech2_port* qt2_get_port_private (struct usb_serial_port*) ; 

__attribute__((used)) static void qt2_process_xmit_flush(struct usb_serial_port *port)
{
	/* obtain the private structure for the port */
	struct quatech2_port *port_extra = qt2_get_port_private(port);
	port_extra->xmit_flush = true;
}