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
struct workqueue {int dummy; } ;
struct turnstile {scalar_t__ ts_priority; int /*<<< orphan*/  ts_waitq; struct workqueue* ts_inheritor; } ;
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 scalar_t__ MAXPRI_THROTTLE ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  workq_deallocate_safe (struct workqueue*) ; 
 int workq_is_current_thread_updating_turnstile (struct workqueue*) ; 
 int /*<<< orphan*/  workq_reference (struct workqueue*) ; 
 int /*<<< orphan*/  workq_schedule_creator_turnstile_redrive (struct workqueue*,int) ; 

__attribute__((used)) static void
turnstile_update_inheritor_workq_priority_chain(struct turnstile *turnstile, spl_t s)
{
	struct workqueue *wq = turnstile->ts_inheritor;
	bool workq_lock_held = workq_is_current_thread_updating_turnstile(wq);

	if (__improbable(turnstile->ts_priority <= MAXPRI_THROTTLE)) {
		waitq_unlock(&turnstile->ts_waitq);
		splx(s);
		return;
	}

	if (!workq_lock_held) workq_reference(wq);
	waitq_unlock(&turnstile->ts_waitq);
	splx(s);

	workq_schedule_creator_turnstile_redrive(wq, workq_lock_held);

	if (!workq_lock_held) workq_deallocate_safe(wq);
}