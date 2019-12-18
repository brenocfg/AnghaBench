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
struct tvec_base {int /*<<< orphan*/  lock; int /*<<< orphan*/  next_timer; } ;
struct timer_list {int /*<<< orphan*/  expires; int /*<<< orphan*/  base; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  debug_activate (struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_add_timer (struct tvec_base*,struct timer_list*) ; 
 struct tvec_base* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tbase_get_deferrable (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (struct timer_list*) ; 
 int /*<<< orphan*/  timer_set_base (struct timer_list*,struct tvec_base*) ; 
 int /*<<< orphan*/  timer_stats_timer_set_start_info (struct timer_list*) ; 
 int /*<<< orphan*/  tvec_bases ; 
 int /*<<< orphan*/  wake_up_idle_cpu (int) ; 

void add_timer_on(struct timer_list *timer, int cpu)
{
	struct tvec_base *base = per_cpu(tvec_bases, cpu);
	unsigned long flags;

	timer_stats_timer_set_start_info(timer);
	BUG_ON(timer_pending(timer) || !timer->function);
	spin_lock_irqsave(&base->lock, flags);
	timer_set_base(timer, base);
	debug_activate(timer, timer->expires);
	if (time_before(timer->expires, base->next_timer) &&
	    !tbase_get_deferrable(timer->base))
		base->next_timer = timer->expires;
	internal_add_timer(base, timer);
	/*
	 * Check whether the other CPU is idle and needs to be
	 * triggered to reevaluate the timer wheel when nohz is
	 * active. We are protected against the other CPU fiddling
	 * with the timer by holding the timer base lock. This also
	 * makes sure that a CPU on the way to idle can not evaluate
	 * the timer wheel.
	 */
	wake_up_idle_cpu(cpu);
	spin_unlock_irqrestore(&base->lock, flags);
}