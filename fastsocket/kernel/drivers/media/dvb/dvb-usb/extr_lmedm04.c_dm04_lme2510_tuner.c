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
struct lme2510_state {int tuner_config; } ;
struct dvb_usb_adapter {TYPE_1__* dev; int /*<<< orphan*/  fe; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; int /*<<< orphan*/  i2c_adap; struct lme2510_state* priv; } ;

/* Variables and functions */
 int ENODEV ; 
#define  TUNER_LG 129 
#define  TUNER_S7395 128 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  ix2505v_attach ; 
 int lme2510_int_service (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  lme_coldreset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lme_tuner ; 
 int /*<<< orphan*/  tda826x_attach ; 

__attribute__((used)) static int dm04_lme2510_tuner(struct dvb_usb_adapter *adap)
{
	struct lme2510_state *st = adap->dev->priv;
	char *tun_msg[] = {"", "TDA8263", "IX2505V"};
	int ret = 0;

	switch (st->tuner_config) {
	case TUNER_LG:
		if (dvb_attach(tda826x_attach, adap->fe, 0xc0,
			&adap->dev->i2c_adap, 1))
			ret = st->tuner_config;
		break;
	case TUNER_S7395:
		if (dvb_attach(ix2505v_attach , adap->fe, &lme_tuner,
			&adap->dev->i2c_adap))
			ret = st->tuner_config;
		break;
	default:
		break;
	}

	if (ret)
		info("TUN Found %s tuner", tun_msg[ret]);
	else {
		info("TUN No tuner found --- reseting device");
		lme_coldreset(adap->dev->udev);
		return -ENODEV;
	}

	/* Start the Interupt & Remote*/
	ret = lme2510_int_service(adap);

	return ret;
}