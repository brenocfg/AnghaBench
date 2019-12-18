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
struct TYPE_5__ {void* set_voltage; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ds3000_attach ; 
 void* dvb_attach (int /*<<< orphan*/ ,TYPE_3__*,int,...) ; 
 int /*<<< orphan*/  dw2104_ds3000_config ; 
 void* dw210x_set_voltage ; 
 int /*<<< orphan*/  earda_config ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  mt312_attach ; 
 int /*<<< orphan*/  stb6000_attach ; 
 int /*<<< orphan*/  stv0288_attach ; 
 int /*<<< orphan*/  zl10039_attach ; 
 int /*<<< orphan*/  zl313_config ; 

__attribute__((used)) static int s6x0_frontend_attach(struct dvb_usb_adapter *d)
{
	d->fe = dvb_attach(mt312_attach, &zl313_config,
			&d->dev->i2c_adap);
	if (d->fe != NULL) {
		if (dvb_attach(zl10039_attach, d->fe, 0x60,
				&d->dev->i2c_adap)) {
			d->fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached zl100313+zl10039!\n");
			return 0;
		}
	}

	d->fe = dvb_attach(stv0288_attach, &earda_config,
			&d->dev->i2c_adap);
	if (d->fe != NULL) {
		if (dvb_attach(stb6000_attach, d->fe, 0x61,
				&d->dev->i2c_adap)) {
			d->fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached stv0288+stb6000!\n");
			return 0;
		}
	}

	d->fe = dvb_attach(ds3000_attach, &dw2104_ds3000_config,
			&d->dev->i2c_adap);
	if (d->fe != NULL) {
		d->fe->ops.set_voltage = dw210x_set_voltage;
		info("Attached ds3000+ds2020!\n");
		return 0;
	}

	return -EIO;
}