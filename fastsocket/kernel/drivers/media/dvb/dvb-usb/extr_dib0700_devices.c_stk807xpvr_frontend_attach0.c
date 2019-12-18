#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIO0 ; 
 int /*<<< orphan*/  GPIO10 ; 
 int /*<<< orphan*/  GPIO4 ; 
 int /*<<< orphan*/  GPIO6 ; 
 int /*<<< orphan*/  GPIO7 ; 
 int /*<<< orphan*/  GPIO9 ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  dib0700_ctrl_clock (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  dib0700_set_gpio (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dib8000_attach ; 
 int /*<<< orphan*/  dib8000_i2c_enumeration (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * dib807x_dib8000_config ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int stk807xpvr_frontend_attach0(struct dvb_usb_adapter *adap)
{
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(500);
	dib0700_set_gpio(adap->dev, GPIO9, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO4, GPIO_OUT, 1);
	dib0700_set_gpio(adap->dev, GPIO7, GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);

	dib0700_ctrl_clock(adap->dev, 72, 1);

	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(10);
	dib0700_set_gpio(adap->dev, GPIO0, GPIO_OUT, 1);

	/* initialize IC 0 */
	dib8000_i2c_enumeration(&adap->dev->i2c_adap, 1, 0x22, 0x80);

	adap->fe = dvb_attach(dib8000_attach, &adap->dev->i2c_adap, 0x80,
			      &dib807x_dib8000_config[0]);

	return adap->fe == NULL ? -ENODEV : 0;
}