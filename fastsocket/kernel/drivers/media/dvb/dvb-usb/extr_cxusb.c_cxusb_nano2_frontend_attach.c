#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_1__* dev; int /*<<< orphan*/ * fe; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DIGITAL ; 
 int EIO ; 
 int /*<<< orphan*/  cxusb_bluebird_gpio_pulse (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  cxusb_bluebird_gpio_rw (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxusb_ctrl_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxusb_mt352_xc3028_config ; 
 int /*<<< orphan*/  cxusb_zl10353_xc3028_config ; 
 void* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  mt352_attach ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zl10353_attach ; 

__attribute__((used)) static int cxusb_nano2_frontend_attach(struct dvb_usb_adapter *adap)
{
	if (usb_set_interface(adap->dev->udev, 0, 1) < 0)
		err("set interface failed");

	cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, NULL, 0, NULL, 0);

	/* reset the tuner and demodulator */
	cxusb_bluebird_gpio_rw(adap->dev, 0x04, 0);
	cxusb_bluebird_gpio_pulse(adap->dev, 0x01, 1);
	cxusb_bluebird_gpio_pulse(adap->dev, 0x02, 1);

	if ((adap->fe = dvb_attach(zl10353_attach,
				   &cxusb_zl10353_xc3028_config,
				   &adap->dev->i2c_adap)) != NULL)
		return 0;

	if ((adap->fe = dvb_attach(mt352_attach,
				   &cxusb_mt352_xc3028_config,
				   &adap->dev->i2c_adap)) != NULL)
		return 0;

	return -EIO;
}