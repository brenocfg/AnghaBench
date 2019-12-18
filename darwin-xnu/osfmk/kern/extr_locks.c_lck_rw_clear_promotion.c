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
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_6__ {scalar_t__ rwlock_count; int sched_flags; } ;

/* Variables and functions */
 int TH_SFLAG_RW_PROMOTED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sched_thread_unpromote_reason (TYPE_1__*,int,uintptr_t) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

void lck_rw_clear_promotion(thread_t thread, uintptr_t trace_obj)
{
	assert(thread->rwlock_count == 0);

	/* Cancel any promotions if the thread had actually blocked while holding a RW lock */
	spl_t s = splsched();
	thread_lock(thread);

	if (thread->sched_flags & TH_SFLAG_RW_PROMOTED)
		sched_thread_unpromote_reason(thread, TH_SFLAG_RW_PROMOTED, trace_obj);

	thread_unlock(thread);
	splx(s);
}