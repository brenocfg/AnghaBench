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
struct work_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ current_pages; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  balloon_mutex ; 
 TYPE_1__ balloon_stats ; 
 int /*<<< orphan*/  balloon_timer ; 
 scalar_t__ current_target () ; 
 scalar_t__ decrease_reservation (long) ; 
 scalar_t__ increase_reservation (long) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void balloon_process(struct work_struct *work)
{
	int need_sleep = 0;
	long credit;

	mutex_lock(&balloon_mutex);

	do {
		credit = current_target() - balloon_stats.current_pages;
		if (credit > 0)
			need_sleep = (increase_reservation(credit) != 0);
		if (credit < 0)
			need_sleep = (decrease_reservation(-credit) != 0);

#ifndef CONFIG_PREEMPT
		if (need_resched())
			schedule();
#endif
	} while ((credit != 0) && !need_sleep);

	/* Schedule more work if there is some still to be done. */
	if (current_target() != balloon_stats.current_pages)
		mod_timer(&balloon_timer, jiffies + HZ);

	mutex_unlock(&balloon_mutex);
}