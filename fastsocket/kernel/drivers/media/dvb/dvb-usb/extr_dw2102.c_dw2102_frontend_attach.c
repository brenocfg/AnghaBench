#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_4__* fe; TYPE_1__* dev; } ;
struct TYPE_6__ {void* set_voltage; } ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_7__ {int /*<<< orphan*/ * i2c_algo; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 void* dvb_attach (int /*<<< orphan*/ ,TYPE_4__*,int,...) ; 
 int /*<<< orphan*/  dw2102_earda_i2c_algo ; 
 int /*<<< orphan*/  dw2102_i2c_algo ; 
 TYPE_3__ dw2102_properties ; 
 int /*<<< orphan*/  dw2102_serit_i2c_algo ; 
 void* dw210x_set_voltage ; 
 int /*<<< orphan*/  earda_config ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  serit_sp1511lhb_config ; 
 int /*<<< orphan*/  sharp_z0194a_config ; 
 int /*<<< orphan*/  si21xx_attach ; 
 int /*<<< orphan*/  stb6000_attach ; 
 int /*<<< orphan*/  stv0288_attach ; 
 int /*<<< orphan*/  stv0299_attach ; 

__attribute__((used)) static int dw2102_frontend_attach(struct dvb_usb_adapter *d)
{
	if (dw2102_properties.i2c_algo == &dw2102_serit_i2c_algo) {
		/*dw2102_properties.adapter->tuner_attach = NULL;*/
		d->fe = dvb_attach(si21xx_attach, &serit_sp1511lhb_config,
					&d->dev->i2c_adap);
		if (d->fe != NULL) {
			d->fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached si21xx!\n");
			return 0;
		}
	}

	if (dw2102_properties.i2c_algo == &dw2102_earda_i2c_algo) {
		d->fe = dvb_attach(stv0288_attach, &earda_config,
					&d->dev->i2c_adap);
		if (d->fe != NULL) {
			if (dvb_attach(stb6000_attach, d->fe, 0x61,
					&d->dev->i2c_adap)) {
				d->fe->ops.set_voltage = dw210x_set_voltage;
				info("Attached stv0288!\n");
				return 0;
			}
		}
	}

	if (dw2102_properties.i2c_algo == &dw2102_i2c_algo) {
		/*dw2102_properties.adapter->tuner_attach = dw2102_tuner_attach;*/
		d->fe = dvb_attach(stv0299_attach, &sharp_z0194a_config,
					&d->dev->i2c_adap);
		if (d->fe != NULL) {
			d->fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached stv0299!\n");
			return 0;
		}
	}
	return -EIO;
}