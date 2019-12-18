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
struct usb_serial {int /*<<< orphan*/ * port; int /*<<< orphan*/  dev; } ;
struct ch341_private {int line_control; int /*<<< orphan*/  baud_rate; int /*<<< orphan*/  delta_msr_wait; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CH341_BIT_DTR ; 
 int CH341_BIT_RTS ; 
 int /*<<< orphan*/  DEFAULT_BAUD_RATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ch341_configure (int /*<<< orphan*/ ,struct ch341_private*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ch341_private*) ; 
 struct ch341_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (int /*<<< orphan*/ ,struct ch341_private*) ; 

__attribute__((used)) static int ch341_attach(struct usb_serial *serial)
{
	struct ch341_private *priv;
	int r;

	dbg("ch341_attach()");

	/* private data */
	priv = kzalloc(sizeof(struct ch341_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	spin_lock_init(&priv->lock);
	init_waitqueue_head(&priv->delta_msr_wait);
	priv->baud_rate = DEFAULT_BAUD_RATE;
	priv->line_control = CH341_BIT_RTS | CH341_BIT_DTR;

	r = ch341_configure(serial->dev, priv);
	if (r < 0)
		goto error;

	usb_set_serial_port_data(serial->port[0], priv);
	return 0;

error:	kfree(priv);
	return r;
}