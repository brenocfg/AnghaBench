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
struct usb_serial_port {TYPE_1__* read_urb; TYPE_1__* interrupt_in_urb; int /*<<< orphan*/  write_wait; } ;
struct usb_serial {struct usb_serial_port** port; } ;
struct mct_u232_private {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct usb_serial_port* context; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct mct_u232_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct mct_u232_private*) ; 

__attribute__((used)) static int mct_u232_startup(struct usb_serial *serial)
{
	struct mct_u232_private *priv;
	struct usb_serial_port *port, *rport;

	priv = kzalloc(sizeof(struct mct_u232_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	spin_lock_init(&priv->lock);
	usb_set_serial_port_data(serial->port[0], priv);

	init_waitqueue_head(&serial->port[0]->write_wait);

	/* Puh, that's dirty */
	port = serial->port[0];
	rport = serial->port[1];
	/* No unlinking, it wasn't submitted yet. */
	usb_free_urb(port->read_urb);
	port->read_urb = rport->interrupt_in_urb;
	rport->interrupt_in_urb = NULL;
	port->read_urb->context = port;

	return 0;
}