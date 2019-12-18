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
typedef  scalar_t__ timer_t ;
struct k_itimer {scalar_t__ it_signal; int /*<<< orphan*/  it_lock; } ;
struct TYPE_2__ {scalar_t__ signal; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 struct k_itimer* idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  posix_timers_id ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct k_itimer *lock_timer(timer_t timer_id, unsigned long *flags)
{
	struct k_itimer *timr;

	rcu_read_lock();
	timr = idr_find(&posix_timers_id, (int)timer_id);
	if (timr) {
		spin_lock_irqsave(&timr->it_lock, *flags);
		if (timr->it_signal == current->signal) {
			rcu_read_unlock();
			return timr;
		}
		spin_unlock_irqrestore(&timr->it_lock, *flags);
	}
	rcu_read_unlock();

	return NULL;
}