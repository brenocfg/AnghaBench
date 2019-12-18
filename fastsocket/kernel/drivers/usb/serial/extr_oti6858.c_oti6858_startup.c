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
struct usb_serial {int num_ports; struct usb_serial_port** port; } ;
struct oti6858_private {int /*<<< orphan*/ * buf; int /*<<< orphan*/  delayed_write_work; int /*<<< orphan*/  delayed_setup_work; struct usb_serial_port* port; int /*<<< orphan*/  intr_wait; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL2303_BUF_SIZE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct oti6858_private*) ; 
 struct oti6858_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * oti6858_buf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oti6858_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_data ; 
 int /*<<< orphan*/  setup_line ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct oti6858_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct oti6858_private*) ; 

__attribute__((used)) static int oti6858_startup(struct usb_serial *serial)
{
	struct usb_serial_port *port = serial->port[0];
	struct oti6858_private *priv;
	int i;

	for (i = 0; i < serial->num_ports; ++i) {
		priv = kzalloc(sizeof(struct oti6858_private), GFP_KERNEL);
		if (!priv)
			break;
		priv->buf = oti6858_buf_alloc(PL2303_BUF_SIZE);
		if (priv->buf == NULL) {
			kfree(priv);
			break;
		}

		spin_lock_init(&priv->lock);
		init_waitqueue_head(&priv->intr_wait);
/*		INIT_WORK(&priv->setup_work, setup_line, serial->port[i]); */
/*		INIT_WORK(&priv->write_work, send_data, serial->port[i]); */
		priv->port = port;
		INIT_DELAYED_WORK(&priv->delayed_setup_work, setup_line);
		INIT_DELAYED_WORK(&priv->delayed_write_work, send_data);

		usb_set_serial_port_data(serial->port[i], priv);
	}
	if (i == serial->num_ports)
		return 0;

	for (--i; i >= 0; --i) {
		priv = usb_get_serial_port_data(serial->port[i]);
		oti6858_buf_free(priv->buf);
		kfree(priv);
		usb_set_serial_port_data(serial->port[i], NULL);
	}
	return -ENOMEM;
}