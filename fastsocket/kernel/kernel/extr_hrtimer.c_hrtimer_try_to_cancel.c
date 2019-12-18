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
struct hrtimer_clock_base {int dummy; } ;
struct hrtimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_callback_running (struct hrtimer*) ; 
 struct hrtimer_clock_base* lock_hrtimer_base (struct hrtimer*,unsigned long*) ; 
 int remove_hrtimer (struct hrtimer*,struct hrtimer_clock_base*) ; 
 int /*<<< orphan*/  unlock_hrtimer_base (struct hrtimer*,unsigned long*) ; 

int hrtimer_try_to_cancel(struct hrtimer *timer)
{
	struct hrtimer_clock_base *base;
	unsigned long flags;
	int ret = -1;

	base = lock_hrtimer_base(timer, &flags);

	if (!hrtimer_callback_running(timer))
		ret = remove_hrtimer(timer, base);

	unlock_hrtimer_base(timer, &flags);

	return ret;

}