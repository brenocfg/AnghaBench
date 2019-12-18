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
struct dvb_usb_adapter {TYPE_1__* dev; int /*<<< orphan*/  fe; struct dibusb_state* priv; } ;
struct dibusb_state {int tuner_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_PLL_TDA665X ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_pll_attach ; 

__attribute__((used)) static int dibusb_panasonic_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct dibusb_state *st = adap->priv;

	st->tuner_addr = 0x60;

	dvb_attach(dvb_pll_attach, adap->fe, 0x60, &adap->dev->i2c_adap,
		   DVB_PLL_TDA665X);
	return 0;
}