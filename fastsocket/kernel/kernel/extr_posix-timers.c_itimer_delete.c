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
struct k_itimer {int /*<<< orphan*/ * it_signal; int /*<<< orphan*/  list; int /*<<< orphan*/  it_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT_ID_SET ; 
 scalar_t__ TIMER_RETRY ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_posix_timer (struct k_itimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_delete_hook (struct k_itimer*) ; 
 int /*<<< orphan*/  unlock_timer (struct k_itimer*,unsigned long) ; 

__attribute__((used)) static void itimer_delete(struct k_itimer *timer)
{
	unsigned long flags;

retry_delete:
	spin_lock_irqsave(&timer->it_lock, flags);

	if (timer_delete_hook(timer) == TIMER_RETRY) {
		unlock_timer(timer, flags);
		goto retry_delete;
	}
	list_del(&timer->list);
	/*
	 * This keeps any tasks waiting on the spin lock from thinking
	 * they got something (see the lock code above).
	 */
	timer->it_signal = NULL;

	unlock_timer(timer, flags);
	release_posix_timer(timer, IT_ID_SET);
}