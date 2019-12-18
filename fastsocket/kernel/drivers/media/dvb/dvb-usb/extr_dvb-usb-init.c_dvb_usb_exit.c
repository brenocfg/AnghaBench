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
struct dvb_usb_device {struct dvb_usb_device* priv; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_USB_STATE_INIT ; 
 int /*<<< orphan*/  deb_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_usb_adapter_exit (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dvb_usb_i2c_exit (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dvb_usb_remote_exit (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  kfree (struct dvb_usb_device*) ; 

__attribute__((used)) static int dvb_usb_exit(struct dvb_usb_device *d)
{
	deb_info("state before exiting everything: %x\n", d->state);
	dvb_usb_remote_exit(d);
	dvb_usb_adapter_exit(d);
	dvb_usb_i2c_exit(d);
	deb_info("state should be zero now: %x\n", d->state);
	d->state = DVB_USB_STATE_INIT;
	kfree(d->priv);
	kfree(d);
	return 0;
}