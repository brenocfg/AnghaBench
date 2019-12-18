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
struct usb_serial_port {struct urb* read_urb; } ;
struct urb {scalar_t__ actual_length; } ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ProcessRxChar(struct tty_struct *tty, struct usb_serial_port *port,
						unsigned char data)
{
	struct urb *urb = port->read_urb;
	if (urb->actual_length)
		tty_insert_flip_char(tty, data, TTY_NORMAL);
}