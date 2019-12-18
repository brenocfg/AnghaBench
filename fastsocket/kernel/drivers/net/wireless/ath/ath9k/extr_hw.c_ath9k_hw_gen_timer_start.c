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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  timer_bits; } ;
struct ath_gen_timer_table {TYPE_1__ timer_mask; } ;
struct ath_hw {struct ath_gen_timer_table hw_gen_timers; } ;
struct ath_gen_timer {size_t index; } ;
struct TYPE_4__ {int mode_mask; int /*<<< orphan*/  mode_addr; int /*<<< orphan*/  period_addr; int /*<<< orphan*/  next_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GENTMR_BIT (int) ; 
 size_t AR_GEN_TIMER_BANK_1_LEN ; 
 int /*<<< orphan*/  AR_IMR_S5 ; 
 int /*<<< orphan*/  AR_IMR_S5_GENTIMER_THRESH ; 
 int /*<<< orphan*/  AR_IMR_S5_GENTIMER_TRIG ; 
 int /*<<< orphan*/  AR_MAC_PCU_GEN_TIMER_TSF_SEL ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HWTIMER ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_gettsf32 (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_2__* gen_tmr_configuration ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ *) ; 

void ath9k_hw_gen_timer_start(struct ath_hw *ah,
			      struct ath_gen_timer *timer,
			      u32 trig_timeout,
			      u32 timer_period)
{
	struct ath_gen_timer_table *timer_table = &ah->hw_gen_timers;
	u32 tsf, timer_next;

	BUG_ON(!timer_period);

	set_bit(timer->index, &timer_table->timer_mask.timer_bits);

	tsf = ath9k_hw_gettsf32(ah);

	timer_next = tsf + trig_timeout;

	ath_dbg(ath9k_hw_common(ah), HWTIMER,
		"current tsf %x period %x timer_next %x\n",
		tsf, timer_period, timer_next);

	/*
	 * Program generic timer registers
	 */
	REG_WRITE(ah, gen_tmr_configuration[timer->index].next_addr,
		 timer_next);
	REG_WRITE(ah, gen_tmr_configuration[timer->index].period_addr,
		  timer_period);
	REG_SET_BIT(ah, gen_tmr_configuration[timer->index].mode_addr,
		    gen_tmr_configuration[timer->index].mode_mask);

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		/*
		 * Starting from AR9462, each generic timer can select which tsf
		 * to use. But we still follow the old rule, 0 - 7 use tsf and
		 * 8 - 15  use tsf2.
		 */
		if ((timer->index < AR_GEN_TIMER_BANK_1_LEN))
			REG_CLR_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL,
				       (1 << timer->index));
		else
			REG_SET_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL,
				       (1 << timer->index));
	}

	/* Enable both trigger and thresh interrupt masks */
	REG_SET_BIT(ah, AR_IMR_S5,
		(SM(AR_GENTMR_BIT(timer->index), AR_IMR_S5_GENTIMER_THRESH) |
		SM(AR_GENTMR_BIT(timer->index), AR_IMR_S5_GENTIMER_TRIG)));
}