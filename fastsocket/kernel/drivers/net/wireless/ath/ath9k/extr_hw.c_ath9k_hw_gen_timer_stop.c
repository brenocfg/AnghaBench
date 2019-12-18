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
struct TYPE_3__ {int /*<<< orphan*/  timer_bits; } ;
struct ath_gen_timer_table {TYPE_1__ timer_mask; } ;
struct ath_hw {struct ath_gen_timer_table hw_gen_timers; } ;
struct ath_gen_timer {size_t index; } ;
struct TYPE_4__ {int mode_mask; int /*<<< orphan*/  mode_addr; } ;

/* Variables and functions */
 size_t AR_FIRST_NDP_TIMER ; 
 int /*<<< orphan*/  AR_GENTMR_BIT (int) ; 
 size_t AR_GEN_TIMER_BANK_1_LEN ; 
 int /*<<< orphan*/  AR_IMR_S5 ; 
 int /*<<< orphan*/  AR_IMR_S5_GENTIMER_THRESH ; 
 int /*<<< orphan*/  AR_IMR_S5_GENTIMER_TRIG ; 
 int /*<<< orphan*/  AR_MAC_PCU_GEN_TIMER_TSF_SEL ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 size_t ATH_MAX_GEN_TIMER ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 TYPE_2__* gen_tmr_configuration ; 

void ath9k_hw_gen_timer_stop(struct ath_hw *ah, struct ath_gen_timer *timer)
{
	struct ath_gen_timer_table *timer_table = &ah->hw_gen_timers;

	if ((timer->index < AR_FIRST_NDP_TIMER) ||
		(timer->index >= ATH_MAX_GEN_TIMER)) {
		return;
	}

	/* Clear generic timer enable bits. */
	REG_CLR_BIT(ah, gen_tmr_configuration[timer->index].mode_addr,
			gen_tmr_configuration[timer->index].mode_mask);

	if (AR_SREV_9462(ah) || AR_SREV_9565(ah)) {
		/*
		 * Need to switch back to TSF if it was using TSF2.
		 */
		if ((timer->index >= AR_GEN_TIMER_BANK_1_LEN)) {
			REG_CLR_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL,
				    (1 << timer->index));
		}
	}

	/* Disable both trigger and thresh interrupt masks */
	REG_CLR_BIT(ah, AR_IMR_S5,
		(SM(AR_GENTMR_BIT(timer->index), AR_IMR_S5_GENTIMER_THRESH) |
		SM(AR_GENTMR_BIT(timer->index), AR_IMR_S5_GENTIMER_TRIG)));

	clear_bit(timer->index, &timer_table->timer_mask.timer_bits);
}