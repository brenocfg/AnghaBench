#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_4__* fe; TYPE_1__* dev; } ;
struct digitv_state {scalar_t__ is_nxt6000; } ;
struct TYPE_6__ {int /*<<< orphan*/  set_params; } ;
struct TYPE_7__ {TYPE_2__ tuner_ops; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {struct digitv_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_PLL_TDED4 ; 
 int ENODEV ; 
 int /*<<< orphan*/  digitv_nxt6000_tuner_set_params ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_pll_attach ; 

__attribute__((used)) static int digitv_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct digitv_state *st = adap->dev->priv;

	if (!dvb_attach(dvb_pll_attach, adap->fe, 0x60, NULL, DVB_PLL_TDED4))
		return -ENODEV;

	if (st->is_nxt6000)
		adap->fe->ops.tuner_ops.set_params = digitv_nxt6000_tuner_set_params;

	return 0;
}