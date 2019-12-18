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
struct usb_serial_port {int /*<<< orphan*/  number; int /*<<< orphan*/  dev; } ;
struct cypress_private {int /*<<< orphan*/  lock; scalar_t__ comm_is_ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cypress_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void cypress_set_dead(struct usb_serial_port *port)
{
	struct cypress_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	if (!priv->comm_is_ok) {
		spin_unlock_irqrestore(&priv->lock, flags);
		return;
	}
	priv->comm_is_ok = 0;
	spin_unlock_irqrestore(&priv->lock, flags);

	dev_err(&port->dev, "cypress_m8 suspending failing port %d - "
		"interval might be too short\n", port->number);
}