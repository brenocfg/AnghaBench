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
typedef  int /*<<< orphan*/  uint32_t ;
struct workqueue {int /*<<< orphan*/  wq_thidlecount; int /*<<< orphan*/  wq_nthreads; int /*<<< orphan*/  wq_flags; int /*<<< orphan*/  wq_thread_call_last_run; } ;
typedef  void* proc_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int TRACE_wq_add_timer ; 
 int /*<<< orphan*/  WORKQ_THREADREQ_CAN_CREATE_THREADS ; 
 int /*<<< orphan*/  WQ_DELAYED_CALL_SCHEDULED ; 
 int /*<<< orphan*/  WQ_IMMEDIATE_CALL_SCHEDULED ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int,struct workqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _wq_flags (struct workqueue*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 int /*<<< orphan*/  os_atomic_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct workqueue* proc_get_wqptr (void*) ; 
 int /*<<< orphan*/  release ; 
 int /*<<< orphan*/  workq_lock_spin (struct workqueue*) ; 
 int /*<<< orphan*/  workq_schedule_creator (void*,struct workqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_unlock (struct workqueue*) ; 

__attribute__((used)) static void
workq_add_new_threads_call(void *_p, void *flags)
{
	proc_t p = _p;
	struct workqueue *wq = proc_get_wqptr(p);
	uint32_t my_flag = (uint32_t)(uintptr_t)flags;

	/*
	 * workq_exit() will set the workqueue to NULL before
	 * it cancels thread calls.
	 */
	if (!wq) return;

	assert((my_flag == WQ_DELAYED_CALL_SCHEDULED) ||
			(my_flag == WQ_IMMEDIATE_CALL_SCHEDULED));

	WQ_TRACE_WQ(TRACE_wq_add_timer | DBG_FUNC_START, wq, _wq_flags(wq),
			wq->wq_nthreads, wq->wq_thidlecount, 0);

	workq_lock_spin(wq);

	wq->wq_thread_call_last_run = mach_absolute_time();
	os_atomic_and(&wq->wq_flags, ~my_flag, release);

	/* This can drop the workqueue lock, and take it again */
	workq_schedule_creator(p, wq, WORKQ_THREADREQ_CAN_CREATE_THREADS);

	workq_unlock(wq);

	WQ_TRACE_WQ(TRACE_wq_add_timer | DBG_FUNC_END, wq, 0,
			wq->wq_nthreads, wq->wq_thidlecount, 0);
}