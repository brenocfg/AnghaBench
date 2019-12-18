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
struct usb_serial_port {int /*<<< orphan*/  bulk_out_size; } ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DEBUG_MAX_PACKET_SIZE ; 
 int usb_serial_generic_open (struct tty_struct*,struct usb_serial_port*) ; 

__attribute__((used)) static int usb_debug_open(struct tty_struct *tty, struct usb_serial_port *port)
{
	port->bulk_out_size = USB_DEBUG_MAX_PACKET_SIZE;
	return usb_serial_generic_open(tty, port);
}