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
struct tvec_base {scalar_t__ next_timer; scalar_t__ timer_jiffies; int /*<<< orphan*/  lock; } ;
struct timer_list {scalar_t__ expires; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_timer (struct timer_list*,int) ; 
 struct tvec_base* lock_timer_base (struct timer_list*,unsigned long*) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tbase_get_deferrable (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (struct timer_list*) ; 
 int /*<<< orphan*/  timer_stats_timer_clear_start_info (struct timer_list*) ; 

int del_timer(struct timer_list *timer)
{
	struct tvec_base *base;
	unsigned long flags;
	int ret = 0;

	timer_stats_timer_clear_start_info(timer);
	if (timer_pending(timer)) {
		base = lock_timer_base(timer, &flags);
		if (timer_pending(timer)) {
			detach_timer(timer, 1);
			if (timer->expires == base->next_timer &&
			    !tbase_get_deferrable(timer->base))
				base->next_timer = base->timer_jiffies;
			ret = 1;
		}
		spin_unlock_irqrestore(&base->lock, flags);
	}

	return ret;
}