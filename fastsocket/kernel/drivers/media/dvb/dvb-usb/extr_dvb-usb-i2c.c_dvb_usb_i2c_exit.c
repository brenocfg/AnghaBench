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
struct dvb_usb_device {int state; int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int DVB_USB_STATE_I2C ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

int dvb_usb_i2c_exit(struct dvb_usb_device *d)
{
	if (d->state & DVB_USB_STATE_I2C)
		i2c_del_adapter(&d->i2c_adap);
	d->state &= ~DVB_USB_STATE_I2C;
	return 0;
}