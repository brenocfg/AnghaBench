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
struct usb_serial_port {int /*<<< orphan*/  dev; } ;
struct tty_struct {int dummy; } ;
struct spcp8x5_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int put_ringbuf (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  spcp8x5_send (struct usb_serial_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct spcp8x5_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int spcp8x5_write(struct tty_struct *tty, struct usb_serial_port *port,
			 const unsigned char *buf, int count)
{
	struct spcp8x5_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;

	dev_dbg(&port->dev, "%d bytes\n", count);

	if (!count)
		return count;

	spin_lock_irqsave(&priv->lock, flags);
	count = put_ringbuf(priv->buf, buf, count);
	spin_unlock_irqrestore(&priv->lock, flags);

	spcp8x5_send(port);

	return count;
}