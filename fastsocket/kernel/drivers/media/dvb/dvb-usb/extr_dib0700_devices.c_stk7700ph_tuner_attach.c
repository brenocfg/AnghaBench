#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct dvb_usb_adapter {TYPE_2__* fe; } ;
struct TYPE_6__ {int /*<<< orphan*/  callback; } ;
struct TYPE_5__ {struct i2c_adapter* i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_TUNER ; 
 int ENODEV ; 
 struct i2c_adapter* dib7000p_get_i2c_master (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stk7700ph_xc3028_callback ; 
 TYPE_1__ stk7700ph_xc3028_config ; 
 int /*<<< orphan*/  xc2028_attach ; 

__attribute__((used)) static int stk7700ph_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct i2c_adapter *tun_i2c;

	tun_i2c = dib7000p_get_i2c_master(adap->fe,
		DIBX000_I2C_INTERFACE_TUNER, 1);

	stk7700ph_xc3028_config.i2c_adap = tun_i2c;

	/* FIXME: generalize & move to common area */
	adap->fe->callback = stk7700ph_xc3028_callback;

	return dvb_attach(xc2028_attach, adap->fe, &stk7700ph_xc3028_config)
		== NULL ? -ENODEV : 0;
}