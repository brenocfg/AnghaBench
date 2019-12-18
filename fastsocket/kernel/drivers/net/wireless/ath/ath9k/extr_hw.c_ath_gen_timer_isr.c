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
typedef  int u32 ;
struct TYPE_2__ {int val; } ;
struct ath_gen_timer_table {struct ath_gen_timer** timers; TYPE_1__ timer_mask; } ;
struct ath_hw {int intr_gen_timer_trigger; int intr_gen_timer_thresh; struct ath_gen_timer_table hw_gen_timers; } ;
struct ath_gen_timer {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* trigger ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* overflow ) (int /*<<< orphan*/ ) ;} ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HWTIMER ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 int rightmost_index (struct ath_gen_timer_table*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void ath_gen_timer_isr(struct ath_hw *ah)
{
	struct ath_gen_timer_table *timer_table = &ah->hw_gen_timers;
	struct ath_gen_timer *timer;
	struct ath_common *common = ath9k_hw_common(ah);
	u32 trigger_mask, thresh_mask, index;

	/* get hardware generic timer interrupt status */
	trigger_mask = ah->intr_gen_timer_trigger;
	thresh_mask = ah->intr_gen_timer_thresh;
	trigger_mask &= timer_table->timer_mask.val;
	thresh_mask &= timer_table->timer_mask.val;

	trigger_mask &= ~thresh_mask;

	while (thresh_mask) {
		index = rightmost_index(timer_table, &thresh_mask);
		timer = timer_table->timers[index];
		BUG_ON(!timer);
		ath_dbg(common, HWTIMER, "TSF overflow for Gen timer %d\n",
			index);
		timer->overflow(timer->arg);
	}

	while (trigger_mask) {
		index = rightmost_index(timer_table, &trigger_mask);
		timer = timer_table->timers[index];
		BUG_ON(!timer);
		ath_dbg(common, HWTIMER,
			"Gen timer[%d] trigger\n", index);
		timer->trigger(timer->arg);
	}
}