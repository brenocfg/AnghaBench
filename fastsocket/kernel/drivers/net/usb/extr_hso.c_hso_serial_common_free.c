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
struct hso_serial {int num_rx_urbs; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/ * rx_data; int /*<<< orphan*/ * rx_urb; int /*<<< orphan*/  minor; TYPE_1__* parent; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_hsotype ; 
 int /*<<< orphan*/  device_remove_file (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_drv ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hso_serial_common_free(struct hso_serial *serial)
{
	int i;

	if (serial->parent->dev)
		device_remove_file(serial->parent->dev, &dev_attr_hsotype);

	tty_unregister_device(tty_drv, serial->minor);

	for (i = 0; i < serial->num_rx_urbs; i++) {
		/* unlink and free RX URB */
		usb_free_urb(serial->rx_urb[i]);
		/* free the RX buffer */
		kfree(serial->rx_data[i]);
	}

	/* unlink and free TX URB */
	usb_free_urb(serial->tx_urb);
	kfree(serial->tx_data);
}