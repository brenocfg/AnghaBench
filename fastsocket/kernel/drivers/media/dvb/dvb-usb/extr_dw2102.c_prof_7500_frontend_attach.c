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
struct TYPE_5__ {int /*<<< orphan*/  set_voltage; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_3__* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw210x_set_voltage ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  prof_7500_stv0900_config ; 
 int /*<<< orphan*/  stv0900_attach ; 

__attribute__((used)) static int prof_7500_frontend_attach(struct dvb_usb_adapter *d)
{
	d->fe = dvb_attach(stv0900_attach, &prof_7500_stv0900_config,
					&d->dev->i2c_adap, 0);
	if (d->fe == NULL)
		return -EIO;
	d->fe->ops.set_voltage = dw210x_set_voltage;

	info("Attached STV0900+STB6100A!\n");

	return 0;
}