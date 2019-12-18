#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; TYPE_1__* dev; } ;
struct dib0700_state {int* mt2060_if1; int is_dib7000pc; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; struct dib0700_state* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIO0 ; 
 int /*<<< orphan*/  GPIO10 ; 
 int /*<<< orphan*/  GPIO6 ; 
 int /*<<< orphan*/  GPIO9 ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  dib0700_ctrl_clock (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  dib0700_set_gpio (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dib7000m_attach ; 
 int /*<<< orphan*/  dib7000p_attach ; 
 scalar_t__ dib7000pc_detection (int /*<<< orphan*/ *) ; 
 void* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stk7700p_dib7000m_config ; 
 int /*<<< orphan*/  stk7700p_dib7000p_config ; 

__attribute__((used)) static int stk7700p_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dib0700_state *st = adap->dev->priv;
	/* unless there is no real power management in DVB - we leave the device on GPIO6 */

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 0); msleep(50);

	dib0700_set_gpio(adap->dev, GPIO6,  GPIO_OUT, 1); msleep(10);
	dib0700_set_gpio(adap->dev, GPIO9,  GPIO_OUT, 1);

	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0); msleep(10);
	dib0700_ctrl_clock(adap->dev, 72, 1);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1); msleep(100);

	dib0700_set_gpio(adap->dev,  GPIO0, GPIO_OUT, 1);

	st->mt2060_if1[0] = 1220;

	if (dib7000pc_detection(&adap->dev->i2c_adap)) {
		adap->fe = dvb_attach(dib7000p_attach, &adap->dev->i2c_adap, 18, &stk7700p_dib7000p_config);
		st->is_dib7000pc = 1;
	} else
		adap->fe = dvb_attach(dib7000m_attach, &adap->dev->i2c_adap, 18, &stk7700p_dib7000m_config);

	return adap->fe == NULL ? -ENODEV : 0;
}