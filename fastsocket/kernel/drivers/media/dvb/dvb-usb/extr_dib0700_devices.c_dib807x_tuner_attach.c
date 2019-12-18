#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct dvb_usb_adapter {scalar_t__ id; TYPE_3__* fe; struct dib0700_adapter_state* priv; } ;
struct dib0700_adapter_state {int /*<<< orphan*/  set_param_save; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_params; } ;
struct TYPE_6__ {TYPE_1__ tuner_ops; } ;
struct TYPE_7__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_TUNER ; 
 int ENODEV ; 
 int /*<<< orphan*/  dib0070_attach ; 
 struct i2c_adapter* dib8000_get_i2c_master (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * dib807x_dib0070_config ; 
 int /*<<< orphan*/  dib807x_set_param_override ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,TYPE_3__*,struct i2c_adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib807x_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct dib0700_adapter_state *st = adap->priv;
	struct i2c_adapter *tun_i2c = dib8000_get_i2c_master(adap->fe,
			DIBX000_I2C_INTERFACE_TUNER, 1);

	if (adap->id == 0) {
		if (dvb_attach(dib0070_attach, adap->fe, tun_i2c,
				&dib807x_dib0070_config[0]) == NULL)
			return -ENODEV;
	} else {
		if (dvb_attach(dib0070_attach, adap->fe, tun_i2c,
				&dib807x_dib0070_config[1]) == NULL)
			return -ENODEV;
	}

	st->set_param_save = adap->fe->ops.tuner_ops.set_params;
	adap->fe->ops.tuner_ops.set_params = dib807x_set_param_override;
	return 0;
}