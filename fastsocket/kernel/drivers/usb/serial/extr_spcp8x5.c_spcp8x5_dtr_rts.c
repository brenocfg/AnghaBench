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
typedef  int u8 ;
struct usb_serial_port {TYPE_1__* serial; } ;
struct spcp8x5_private {int line_control; int /*<<< orphan*/  type; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MCR_CONTROL_LINE_DTR ; 
 int MCR_CONTROL_LINE_RTS ; 
 int /*<<< orphan*/  spcp8x5_set_ctrlLine (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct spcp8x5_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void spcp8x5_dtr_rts(struct usb_serial_port *port, int on)
{
	struct spcp8x5_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;
	u8 control;

	spin_lock_irqsave(&priv->lock, flags);
	if (on)
		priv->line_control = MCR_CONTROL_LINE_DTR
						| MCR_CONTROL_LINE_RTS;
	else
		priv->line_control &= ~ (MCR_CONTROL_LINE_DTR
						| MCR_CONTROL_LINE_RTS);
	control = priv->line_control;
	spin_unlock_irqrestore(&priv->lock, flags);
	spcp8x5_set_ctrlLine(port->serial->dev, control , priv->type);
}