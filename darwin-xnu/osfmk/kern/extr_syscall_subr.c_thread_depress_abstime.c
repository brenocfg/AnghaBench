#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_6__ {int sched_flags; int /*<<< orphan*/  depress_timer_active; int /*<<< orphan*/  depress_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETPRI_LAZY ; 
 int TH_SFLAG_DEPRESS ; 
 int TH_SFLAG_POLLDEPRESS ; 
 int /*<<< orphan*/  TIMER_CALL_USER_CRITICAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (scalar_t__,scalar_t__*) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_recompute_sched_pri (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_call_enter (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void
thread_depress_abstime(uint64_t interval)
{
	thread_t self = current_thread();

	spl_t s = splsched();
	thread_lock(self);

	assert((self->sched_flags & TH_SFLAG_DEPRESS) == 0);

	if ((self->sched_flags & TH_SFLAG_POLLDEPRESS) == 0) {
		self->sched_flags |= TH_SFLAG_DEPRESS;
		thread_recompute_sched_pri(self, SETPRI_LAZY);

		if (interval != 0) {
			uint64_t deadline;

			clock_absolutetime_interval_to_deadline(interval, &deadline);
			if (!timer_call_enter(&self->depress_timer, deadline, TIMER_CALL_USER_CRITICAL))
				self->depress_timer_active++;
		}
	}

	thread_unlock(self);
	splx(s);
}