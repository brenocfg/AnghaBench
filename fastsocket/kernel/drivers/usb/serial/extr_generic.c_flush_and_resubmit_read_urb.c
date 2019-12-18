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
struct usb_serial_port {int /*<<< orphan*/  sysrq; int /*<<< orphan*/  console; int /*<<< orphan*/  port; struct urb* read_urb; } ;
struct urb {int actual_length; scalar_t__ transfer_buffer; } ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_struct*,char*,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_serial_generic_resubmit_read_urb (struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_serial_handle_sysrq_char (struct tty_struct*,struct usb_serial_port*,char) ; 

__attribute__((used)) static void flush_and_resubmit_read_urb(struct usb_serial_port *port)
{
	struct urb *urb = port->read_urb;
	struct tty_struct *tty = tty_port_tty_get(&port->port);
	char *ch = (char *)urb->transfer_buffer;
	int i;

	if (!tty)
		goto done;

	/* The per character mucking around with sysrq path it too slow for
	   stuff like 3G modems, so shortcircuit it in the 99.9999999% of cases
	   where the USB serial is not a console anyway */
	if (!port->console || !port->sysrq)
		tty_insert_flip_string(tty, ch, urb->actual_length);
	else {
		/* Push data to tty */
		for (i = 0; i < urb->actual_length; i++, ch++) {
			if (!usb_serial_handle_sysrq_char(tty, port, *ch))
				tty_insert_flip_char(tty, *ch, TTY_NORMAL);
		}
	}
	tty_flip_buffer_push(tty);
	tty_kref_put(tty);
done:
	usb_serial_generic_resubmit_read_urb(port, GFP_ATOMIC);
}