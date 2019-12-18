#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {TYPE_1__* serial; } ;
struct tty_struct {int dummy; } ;
struct ktermios {int dummy; } ;
struct ch341_private {unsigned int baud_rate; int line_control; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CH341_BIT_DTR ; 
 int CH341_BIT_RTS ; 
 int /*<<< orphan*/  ch341_set_baudrate (int /*<<< orphan*/ ,struct ch341_private*) ; 
 int /*<<< orphan*/  ch341_set_handshake (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int tty_get_baud_rate (struct tty_struct*) ; 
 struct ch341_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void ch341_set_termios(struct tty_struct *tty,
		struct usb_serial_port *port, struct ktermios *old_termios)
{
	struct ch341_private *priv = usb_get_serial_port_data(port);
	unsigned baud_rate;
	unsigned long flags;

	dbg("ch341_set_termios()");

	baud_rate = tty_get_baud_rate(tty);

	priv->baud_rate = baud_rate;

	if (baud_rate) {
		spin_lock_irqsave(&priv->lock, flags);
		priv->line_control |= (CH341_BIT_DTR | CH341_BIT_RTS);
		spin_unlock_irqrestore(&priv->lock, flags);
		ch341_set_baudrate(port->serial->dev, priv);
	} else {
		spin_lock_irqsave(&priv->lock, flags);
		priv->line_control &= ~(CH341_BIT_DTR | CH341_BIT_RTS);
		spin_unlock_irqrestore(&priv->lock, flags);
	}

	ch341_set_handshake(port->serial->dev, priv->line_control);

	/* Unimplemented:
	 * (cflag & CSIZE) : data bits [5, 8]
	 * (cflag & PARENB) : parity {NONE, EVEN, ODD}
	 * (cflag & CSTOPB) : stop bits [1, 2]
	 */
}