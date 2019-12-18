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
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcw_mxl5007t_config ; 
 int /*<<< orphan*/  mxl5007t_attach ; 

__attribute__((used)) static int mxl5007t_tuner_attach(struct dvb_usb_adapter *adap)
{
	return dvb_attach(mxl5007t_attach, adap->fe,
			  &adap->dev->i2c_adap, 0x60,
			  &hcw_mxl5007t_config) == NULL ? -ENODEV : 0;
}