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
 int ENODEV ; 
 int /*<<< orphan*/  dib7000p_attach ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stk7070pd_dib7000p_config ; 

__attribute__((used)) static int stk7070pd_frontend_attach1(struct dvb_usb_adapter *adap)
{
	adap->fe = dvb_attach(dib7000p_attach, &adap->dev->i2c_adap, 0x82, &stk7070pd_dib7000p_config[1]);
	return adap->fe == NULL ? -ENODEV : 0;
}