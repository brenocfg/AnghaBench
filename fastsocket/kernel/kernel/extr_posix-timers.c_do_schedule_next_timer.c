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
struct siginfo {scalar_t__ si_sys_private; int /*<<< orphan*/  si_overrun; int /*<<< orphan*/  si_tid; } ;
struct k_itimer {scalar_t__ it_requeue_pending; scalar_t__ it_clock; scalar_t__ it_overrun_last; } ;

/* Variables and functions */
 struct k_itimer* lock_timer (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  posix_cpu_timer_schedule (struct k_itimer*) ; 
 int /*<<< orphan*/  schedule_next_timer (struct k_itimer*) ; 
 int /*<<< orphan*/  unlock_timer (struct k_itimer*,unsigned long) ; 

void do_schedule_next_timer(struct siginfo *info)
{
	struct k_itimer *timr;
	unsigned long flags;

	timr = lock_timer(info->si_tid, &flags);

	if (timr && timr->it_requeue_pending == info->si_sys_private) {
		if (timr->it_clock < 0)
			posix_cpu_timer_schedule(timr);
		else
			schedule_next_timer(timr);

		info->si_overrun += timr->it_overrun_last;
	}

	if (timr)
		unlock_timer(timr, flags);
}