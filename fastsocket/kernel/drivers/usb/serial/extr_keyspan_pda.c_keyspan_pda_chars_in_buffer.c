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
struct usb_serial_port {int /*<<< orphan*/  lock; scalar_t__ write_urb_busy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct keyspan_pda_private {scalar_t__ tx_throttled; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct keyspan_pda_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int keyspan_pda_chars_in_buffer(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct keyspan_pda_private *priv;
	unsigned long flags;
	int ret = 0;

	priv = usb_get_serial_port_data(port);

	/* when throttled, return at least WAKEUP_CHARS to tell select() (via
	   n_tty.c:normal_poll() ) that we're not writeable. */

	spin_lock_irqsave(&port->lock, flags);
	if (port->write_urb_busy || priv->tx_throttled)
		ret = 256;
	spin_unlock_irqrestore(&port->lock, flags);
	return ret;
}