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
struct TYPE_2__ {int /*<<< orphan*/  rcu; } ;
struct k_itimer {TYPE_1__ it; int /*<<< orphan*/  sigq; int /*<<< orphan*/  it_pid; int /*<<< orphan*/  it_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_itimer_rcu_free ; 
 int /*<<< orphan*/  posix_timers_id ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigqueue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void release_posix_timer(struct k_itimer *tmr, int it_id_set)
{
	if (it_id_set) {
		unsigned long flags;
		spin_lock_irqsave(&idr_lock, flags);
		idr_remove(&posix_timers_id, tmr->it_id);
		spin_unlock_irqrestore(&idr_lock, flags);
	}
	put_pid(tmr->it_pid);
	sigqueue_free(tmr->sigq);
	call_rcu(&tmr->it.rcu, k_itimer_rcu_free);
}