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
struct TYPE_5__ {int /*<<< orphan*/ * i2c_gate_ctrl; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dtv5100_zl10353_config ; 
 TYPE_3__* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zl10353_attach ; 

__attribute__((used)) static int dtv5100_frontend_attach(struct dvb_usb_adapter *adap)
{
	adap->fe = dvb_attach(zl10353_attach, &dtv5100_zl10353_config,
			      &adap->dev->i2c_adap);
	if (adap->fe == NULL)
		return -EIO;

	/* disable i2c gate, or it won't work... is this safe? */
	adap->fe->ops.i2c_gate_ctrl = NULL;

	return 0;
}