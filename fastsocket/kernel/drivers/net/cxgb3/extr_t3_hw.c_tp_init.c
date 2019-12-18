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
struct tp_params {int dummy; } ;
struct TYPE_3__ {int cclk; } ;
struct TYPE_4__ {TYPE_1__ vpd; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_RESET ; 
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*) ; 
 int /*<<< orphan*/  F_FLSTINITENABLE ; 
 int /*<<< orphan*/  F_TPRESET ; 
 scalar_t__ is_offload (struct adapter*) ; 
 int /*<<< orphan*/  t3_set_vlan_accel (struct adapter*,int,int /*<<< orphan*/ ) ; 
 int t3_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_config (struct adapter*,struct tp_params const*) ; 
 int /*<<< orphan*/  tp_set_timers (struct adapter*,int) ; 

__attribute__((used)) static int tp_init(struct adapter *adap, const struct tp_params *p)
{
	int busy = 0;

	tp_config(adap, p);
	t3_set_vlan_accel(adap, 3, 0);

	if (is_offload(adap)) {
		tp_set_timers(adap, adap->params.vpd.cclk * 1000);
		t3_write_reg(adap, A_TP_RESET, F_FLSTINITENABLE);
		busy = t3_wait_op_done(adap, A_TP_RESET, F_FLSTINITENABLE,
				       0, 1000, 5);
		if (busy)
			CH_ERR(adap, "TP initialization timed out\n");
	}

	if (!busy)
		t3_write_reg(adap, A_TP_RESET, F_TPRESET);
	return busy;
}