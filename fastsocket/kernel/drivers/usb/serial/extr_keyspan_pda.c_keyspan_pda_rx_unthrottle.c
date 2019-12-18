#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {TYPE_2__* interrupt_in_urb; TYPE_1__* serial; int /*<<< orphan*/  number; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 scalar_t__ usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyspan_pda_rx_unthrottle(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	/* just restart the receive interrupt URB */
	dbg("keyspan_pda_rx_unthrottle port %d", port->number);
	port->interrupt_in_urb->dev = port->serial->dev;
	if (usb_submit_urb(port->interrupt_in_urb, GFP_KERNEL))
		dbg(" usb_submit_urb(read urb) failed");
	return;
}