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
struct visor_private {int /*<<< orphan*/  lock; } ;
struct usb_serial_port {int dummy; } ;
struct usb_serial {int num_ports; struct usb_serial_port** port; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct visor_private*) ; 
 struct visor_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct visor_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct visor_private*) ; 

__attribute__((used)) static int generic_startup(struct usb_serial *serial)
{
	struct usb_serial_port **ports = serial->port;
	struct visor_private *priv;
	int i;

	for (i = 0; i < serial->num_ports; ++i) {
		priv = kzalloc(sizeof(*priv), GFP_KERNEL);
		if (!priv) {
			while (i-- != 0) {
				priv = usb_get_serial_port_data(ports[i]);
				usb_set_serial_port_data(ports[i], NULL);
				kfree(priv);
			}
			return -ENOMEM;
		}
		spin_lock_init(&priv->lock);
		usb_set_serial_port_data(ports[i], priv);
	}
	return 0;
}