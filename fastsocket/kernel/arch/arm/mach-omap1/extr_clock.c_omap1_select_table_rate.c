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
struct mpu_rate {long rate; scalar_t__ xtal; scalar_t__ pll_rate; int ckctl_val; int /*<<< orphan*/  dpllctl_val; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {scalar_t__ rate; } ;
struct TYPE_3__ {scalar_t__ rate; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__ ck_dpll1 ; 
 TYPE_1__ ck_ref ; 
 scalar_t__ cpu_is_omap730 () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  omap_sram_reprogram_clock (int /*<<< orphan*/ ,int) ; 
 struct mpu_rate* rate_table ; 
 struct clk virtual_ck_mpu ; 

__attribute__((used)) static int omap1_select_table_rate(struct clk * clk, unsigned long rate)
{
	/* Find the highest supported frequency <= rate and switch to it */
	struct mpu_rate * ptr;

	if (clk != &virtual_ck_mpu)
		return -EINVAL;

	for (ptr = rate_table; ptr->rate; ptr++) {
		if (ptr->xtal != ck_ref.rate)
			continue;

		/* DPLL1 cannot be reprogrammed without risking system crash */
		if (likely(ck_dpll1.rate!=0) && ptr->pll_rate != ck_dpll1.rate)
			continue;

		/* Can check only after xtal frequency check */
		if (ptr->rate <= rate)
			break;
	}

	if (!ptr->rate)
		return -EINVAL;

	/*
	 * In most cases we should not need to reprogram DPLL.
	 * Reprogramming the DPLL is tricky, it must be done from SRAM.
	 * (on 730, bit 13 must always be 1)
	 */
	if (cpu_is_omap730())
		omap_sram_reprogram_clock(ptr->dpllctl_val, ptr->ckctl_val | 0x2000);
	else
		omap_sram_reprogram_clock(ptr->dpllctl_val, ptr->ckctl_val);

	ck_dpll1.rate = ptr->pll_rate;
	return 0;
}