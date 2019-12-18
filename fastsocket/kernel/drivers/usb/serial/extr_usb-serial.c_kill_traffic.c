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
struct usb_serial_port {int /*<<< orphan*/  interrupt_out_urb; int /*<<< orphan*/  interrupt_in_urb; int /*<<< orphan*/  read_urb; int /*<<< orphan*/  write_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kill_traffic(struct usb_serial_port *port)
{
	usb_kill_urb(port->read_urb);
	usb_kill_urb(port->write_urb);
	/*
	 * This is tricky.
	 * Some drivers submit the read_urb in the
	 * handler for the write_urb or vice versa
	 * this order determines the order in which
	 * usb_kill_urb() must be used to reliably
	 * kill the URBs. As it is unknown here,
	 * both orders must be used in turn.
	 * The call below is not redundant.
	 */
	usb_kill_urb(port->read_urb);
	usb_kill_urb(port->interrupt_in_urb);
	usb_kill_urb(port->interrupt_out_urb);
}