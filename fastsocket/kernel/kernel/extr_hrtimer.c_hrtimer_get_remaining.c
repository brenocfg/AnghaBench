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
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_expires_remaining (struct hrtimer const*) ; 
 struct hrtimer_clock_base* lock_hrtimer_base (struct hrtimer const*,unsigned long*) ; 
 int /*<<< orphan*/  unlock_hrtimer_base (struct hrtimer const*,unsigned long*) ; 

ktime_t hrtimer_get_remaining(const struct hrtimer *timer)
{
	struct hrtimer_clock_base *base;
	unsigned long flags;
	ktime_t rem;

	base = lock_hrtimer_base(timer, &flags);
	rem = hrtimer_expires_remaining(timer);
	unlock_hrtimer_base(timer, &flags);

	return rem;
}