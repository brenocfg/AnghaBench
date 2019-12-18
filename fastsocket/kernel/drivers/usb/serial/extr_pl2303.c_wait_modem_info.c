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
struct pl2303_private {unsigned int line_status; int /*<<< orphan*/  lock; int /*<<< orphan*/  delta_msr_wait; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RNG ; 
 unsigned int UART_CTS ; 
 unsigned int UART_DCD ; 
 unsigned int UART_DSR ; 
 unsigned int UART_RING ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  interruptible_sleep_on (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pl2303_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int wait_modem_info(struct usb_serial_port *port, unsigned int arg)
{
	struct pl2303_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;
	unsigned int prevstatus;
	unsigned int status;
	unsigned int changed;

	spin_lock_irqsave(&priv->lock, flags);
	prevstatus = priv->line_status;
	spin_unlock_irqrestore(&priv->lock, flags);

	while (1) {
		interruptible_sleep_on(&priv->delta_msr_wait);
		/* see if a signal did it */
		if (signal_pending(current))
			return -ERESTARTSYS;

		spin_lock_irqsave(&priv->lock, flags);
		status = priv->line_status;
		spin_unlock_irqrestore(&priv->lock, flags);

		changed = prevstatus ^ status;

		if (((arg & TIOCM_RNG) && (changed & UART_RING)) ||
		    ((arg & TIOCM_DSR) && (changed & UART_DSR)) ||
		    ((arg & TIOCM_CD)  && (changed & UART_DCD)) ||
		    ((arg & TIOCM_CTS) && (changed & UART_CTS))) {
			return 0;
		}
		prevstatus = status;
	}
	/* NOTREACHED */
	return 0;
}