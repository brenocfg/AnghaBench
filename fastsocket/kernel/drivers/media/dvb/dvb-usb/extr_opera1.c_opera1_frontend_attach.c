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
 TYPE_3__* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  opera1_set_voltage ; 
 int /*<<< orphan*/  opera1_stv0299_config ; 
 int /*<<< orphan*/  stv0299_attach ; 

__attribute__((used)) static int opera1_frontend_attach(struct dvb_usb_adapter *d)
{
	if ((d->fe =
	     dvb_attach(stv0299_attach, &opera1_stv0299_config,
			&d->dev->i2c_adap)) != NULL) {
		d->fe->ops.set_voltage = opera1_set_voltage;
		return 0;
	}
	info("not attached stv0299");
	return -EIO;
}