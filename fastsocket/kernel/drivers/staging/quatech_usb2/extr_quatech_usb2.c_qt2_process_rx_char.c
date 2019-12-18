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
struct usb_serial_port {TYPE_2__* serial; int /*<<< orphan*/  port; } ;
struct urb {scalar_t__ actual_length; } ;
struct tty_struct {int dummy; } ;
struct TYPE_4__ {TYPE_1__** port; } ;
struct TYPE_3__ {struct urb* read_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_buffer_request_room (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_struct*,unsigned char*,int) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qt2_process_rx_char(struct usb_serial_port *port,
	unsigned char data)
{
	/* get the tty_struct for this port */
	struct tty_struct *tty = tty_port_tty_get(&(port->port));
	/* get the URB with the data in to push */
	struct urb *urb = port->serial->port[0]->read_urb;

	if (tty && urb->actual_length) {
		tty_buffer_request_room(tty, 1);
		tty_insert_flip_string(tty, &data, 1);
		/* should this be commented out here? */
		/*tty_flip_buffer_push(tty);*/
	}
}