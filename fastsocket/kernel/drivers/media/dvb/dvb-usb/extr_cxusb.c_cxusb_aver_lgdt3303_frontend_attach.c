#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cxusb_aver_lgdt3303_config ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lgdt330x_attach ; 

__attribute__((used)) static int cxusb_aver_lgdt3303_frontend_attach(struct dvb_usb_adapter *adap)
{
	adap->fe = dvb_attach(lgdt330x_attach, &cxusb_aver_lgdt3303_config,
			      &adap->dev->i2c_adap);
	if (adap->fe != NULL)
		return 0;

	return -EIO;
}