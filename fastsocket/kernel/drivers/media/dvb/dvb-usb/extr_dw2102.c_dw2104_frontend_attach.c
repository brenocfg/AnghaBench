#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_3__* fe; TYPE_1__* dev; } ;
struct dvb_tuner_ops {int /*<<< orphan*/  get_bandwidth; int /*<<< orphan*/  set_bandwidth; int /*<<< orphan*/  get_frequency; int /*<<< orphan*/  set_frequency; } ;
struct TYPE_5__ {void* set_voltage; struct dvb_tuner_ops tuner_ops; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cx24116_attach ; 
 int demod_probe ; 
 int /*<<< orphan*/  ds3000_attach ; 
 void* dvb_attach (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  dw2104_config ; 
 int /*<<< orphan*/  dw2104_ds3000_config ; 
 int /*<<< orphan*/  dw2104_stv0900_config ; 
 int /*<<< orphan*/  dw2104_stv6110_config ; 
 int /*<<< orphan*/  dw2104a_stb6100_config ; 
 int /*<<< orphan*/  dw2104a_stv0900_config ; 
 void* dw210x_set_voltage ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  stb6100_attach ; 
 int /*<<< orphan*/  stb6100_get_bandw ; 
 int /*<<< orphan*/  stb6100_get_freq ; 
 int /*<<< orphan*/  stb6100_set_bandw ; 
 int /*<<< orphan*/  stb6100_set_freq ; 
 int /*<<< orphan*/  stv0900_attach ; 
 int /*<<< orphan*/  stv6110_attach ; 

__attribute__((used)) static int dw2104_frontend_attach(struct dvb_usb_adapter *d)
{
	struct dvb_tuner_ops *tuner_ops = NULL;

	if (demod_probe & 4) {
		d->fe = dvb_attach(stv0900_attach, &dw2104a_stv0900_config,
				&d->dev->i2c_adap, 0);
		if (d->fe != NULL) {
			if (dvb_attach(stb6100_attach, d->fe,
					&dw2104a_stb6100_config,
					&d->dev->i2c_adap)) {
				tuner_ops = &d->fe->ops.tuner_ops;
				tuner_ops->set_frequency = stb6100_set_freq;
				tuner_ops->get_frequency = stb6100_get_freq;
				tuner_ops->set_bandwidth = stb6100_set_bandw;
				tuner_ops->get_bandwidth = stb6100_get_bandw;
				d->fe->ops.set_voltage = dw210x_set_voltage;
				info("Attached STV0900+STB6100!\n");
				return 0;
			}
		}
	}

	if (demod_probe & 2) {
		d->fe = dvb_attach(stv0900_attach, &dw2104_stv0900_config,
				&d->dev->i2c_adap, 0);
		if (d->fe != NULL) {
			if (dvb_attach(stv6110_attach, d->fe,
					&dw2104_stv6110_config,
					&d->dev->i2c_adap)) {
				d->fe->ops.set_voltage = dw210x_set_voltage;
				info("Attached STV0900+STV6110A!\n");
				return 0;
			}
		}
	}

	if (demod_probe & 1) {
		d->fe = dvb_attach(cx24116_attach, &dw2104_config,
				&d->dev->i2c_adap);
		if (d->fe != NULL) {
			d->fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached cx24116!\n");
			return 0;
		}
	}

	d->fe = dvb_attach(ds3000_attach, &dw2104_ds3000_config,
			&d->dev->i2c_adap);
	if (d->fe != NULL) {
		d->fe->ops.set_voltage = dw210x_set_voltage;
		info("Attached DS3000!\n");
		return 0;
	}

	return -EIO;
}