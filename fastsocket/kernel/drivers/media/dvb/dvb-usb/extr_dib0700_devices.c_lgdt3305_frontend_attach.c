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
struct dib0700_state {int fw_use_new_i2c_api; int disable_streaming_master_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; struct dib0700_state* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIO10 ; 
 int /*<<< orphan*/  GPIO6 ; 
 int /*<<< orphan*/  GPIO_OUT ; 
 int /*<<< orphan*/  dib0700_set_gpio (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcw_lgdt3305_config ; 
 int /*<<< orphan*/  lgdt3305_attach ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int lgdt3305_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dib0700_state *st = adap->dev->priv;

	/* Make use of the new i2c functions from FW 1.20 */
	st->fw_use_new_i2c_api = 1;

	st->disable_streaming_master_mode = 1;

	/* fe power enable */
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO6, GPIO_OUT, 1);
	msleep(30);

	/* demod reset */
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 0);
	msleep(30);
	dib0700_set_gpio(adap->dev, GPIO10, GPIO_OUT, 1);
	msleep(30);

	adap->fe = dvb_attach(lgdt3305_attach,
			      &hcw_lgdt3305_config,
			      &adap->dev->i2c_adap);

	return adap->fe == NULL ? -ENODEV : 0;
}