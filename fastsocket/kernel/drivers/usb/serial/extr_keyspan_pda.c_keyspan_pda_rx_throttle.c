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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; int /*<<< orphan*/  number; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyspan_pda_rx_throttle(struct tty_struct *tty)
{
	/* stop receiving characters. We just turn off the URB request, and
	   let chars pile up in the device. If we're doing hardware
	   flowcontrol, the device will signal the other end when its buffer
	   fills up. If we're doing XON/XOFF, this would be a good time to
	   send an XOFF, although it might make sense to foist that off
	   upon the device too. */
	struct usb_serial_port *port = tty->driver_data;
	dbg("keyspan_pda_rx_throttle port %d", port->number);
	usb_kill_urb(port->interrupt_in_urb);
}