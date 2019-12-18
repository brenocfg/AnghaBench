#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ath_gen_timer_table {int /*<<< orphan*/ ** timers; } ;
struct ath_hw {struct ath_gen_timer_table hw_gen_timers; } ;
struct ath_gen_timer {size_t index; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ath_gen_timer*) ; 

void ath_gen_timer_free(struct ath_hw *ah, struct ath_gen_timer *timer)
{
	struct ath_gen_timer_table *timer_table = &ah->hw_gen_timers;

	/* free the hardware generic timer slot */
	timer_table->timers[timer->index] = NULL;
	kfree(timer);
}