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

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  LW_URGENT ; 
 int /*<<< orphan*/  __cancel_delayed_work (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  linkwatch_flags ; 
 unsigned long linkwatch_nextevent ; 
 int /*<<< orphan*/  linkwatch_work ; 
 int schedule_delayed_watch (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void linkwatch_schedule_work(int urgent)
{
	unsigned long delay = linkwatch_nextevent - jiffies;

	if (test_bit(LW_URGENT, &linkwatch_flags))
		return;

	/* Minimise down-time: drop delay for up event. */
	if (urgent) {
		if (test_and_set_bit(LW_URGENT, &linkwatch_flags))
			return;
		delay = 0;
	}

	/* If we wrap around we'll delay it by at most HZ. */
	if (delay > HZ)
		delay = 0;

	/*
	 * This is true if we've scheduled it immeditately or if we don't
	 * need an immediate execution and it's already pending.
	 */
	if (schedule_delayed_watch(&linkwatch_work, delay) == !delay)
		return;

	/* Don't bother if there is nothing urgent. */
	if (!test_bit(LW_URGENT, &linkwatch_flags))
		return;

	/* It's already running which is good enough. */
	if (!__cancel_delayed_work(&linkwatch_work))
		return;

	/* Otherwise we reschedule it again for immediate exection. */
	schedule_delayed_watch(&linkwatch_work, 0);
}