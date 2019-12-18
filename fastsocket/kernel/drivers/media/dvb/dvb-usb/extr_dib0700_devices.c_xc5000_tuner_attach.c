#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_1__* dev; TYPE_2__* fe; } ;
struct TYPE_4__ {int /*<<< orphan*/  callback; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dib0700_xc5000_tuner_callback ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5h1411_xc5000_tunerconfig ; 
 int /*<<< orphan*/  xc5000_attach ; 

__attribute__((used)) static int xc5000_tuner_attach(struct dvb_usb_adapter *adap)
{
	/* FIXME: generalize & move to common area */
	adap->fe->callback = dib0700_xc5000_tuner_callback;

	return dvb_attach(xc5000_attach, adap->fe, &adap->dev->i2c_adap,
			  &s5h1411_xc5000_tunerconfig)
		== NULL ? -ENODEV : 0;
}