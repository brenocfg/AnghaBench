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
struct dvb_usb_adapter {TYPE_1__* dev; int /*<<< orphan*/  fe; } ;
struct dvb_frontend {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max2165_attach ; 
 int /*<<< orphan*/  mygica_d689_max2165_cfg ; 

__attribute__((used)) static int cxusb_mygica_d689_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct dvb_frontend *fe;
	fe = dvb_attach(max2165_attach, adap->fe,
			&adap->dev->i2c_adap, &mygica_d689_max2165_cfg);
	return (fe == NULL) ? -EIO : 0;
}