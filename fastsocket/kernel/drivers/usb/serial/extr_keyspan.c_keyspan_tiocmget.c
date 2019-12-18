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
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct keyspan_port_private {scalar_t__ ri_state; scalar_t__ dcd_state; scalar_t__ dsr_state; scalar_t__ cts_state; scalar_t__ dtr_state; scalar_t__ rts_state; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RNG ; 
 unsigned int TIOCM_RTS ; 
 struct keyspan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int keyspan_tiocmget(struct tty_struct *tty, struct file *file)
{
	struct usb_serial_port *port = tty->driver_data;
	struct keyspan_port_private *p_priv = usb_get_serial_port_data(port);
	unsigned int			value;

	value = ((p_priv->rts_state) ? TIOCM_RTS : 0) |
		((p_priv->dtr_state) ? TIOCM_DTR : 0) |
		((p_priv->cts_state) ? TIOCM_CTS : 0) |
		((p_priv->dsr_state) ? TIOCM_DSR : 0) |
		((p_priv->dcd_state) ? TIOCM_CAR : 0) |
		((p_priv->ri_state) ? TIOCM_RNG : 0);

	return value;
}