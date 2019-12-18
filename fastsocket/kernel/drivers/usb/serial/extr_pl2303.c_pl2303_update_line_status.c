#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  scalar_t__ u16 ;
struct usb_serial_port {TYPE_3__* serial; } ;
struct pl2303_private {unsigned char line_status; int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 scalar_t__ SIEMENS_PRODUCT_ID_SX1 ; 
 scalar_t__ SIEMENS_PRODUCT_ID_X65 ; 
 scalar_t__ SIEMENS_PRODUCT_ID_X75 ; 
 scalar_t__ SIEMENS_VENDOR_ID ; 
 int UART_BREAK_ERROR ; 
 unsigned int UART_STATE ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pl2303_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_handle_break (struct usb_serial_port*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pl2303_update_line_status(struct usb_serial_port *port,
				      unsigned char *data,
				      unsigned int actual_length)
{

	struct pl2303_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;
	u8 status_idx = UART_STATE;
	u8 length = UART_STATE + 1;
	u16 idv, idp;

	idv = le16_to_cpu(port->serial->dev->descriptor.idVendor);
	idp = le16_to_cpu(port->serial->dev->descriptor.idProduct);


	if (idv == SIEMENS_VENDOR_ID) {
		if (idp == SIEMENS_PRODUCT_ID_X65 ||
		    idp == SIEMENS_PRODUCT_ID_SX1 ||
		    idp == SIEMENS_PRODUCT_ID_X75) {

			length = 1;
			status_idx = 0;
		}
	}

	if (actual_length < length)
		return;

	/* Save off the uart status for others to look at */
	spin_lock_irqsave(&priv->lock, flags);
	priv->line_status = data[status_idx];
	spin_unlock_irqrestore(&priv->lock, flags);
	if (priv->line_status & UART_BREAK_ERROR)
		usb_serial_handle_break(port);
	wake_up_interruptible(&priv->delta_msr_wait);
}