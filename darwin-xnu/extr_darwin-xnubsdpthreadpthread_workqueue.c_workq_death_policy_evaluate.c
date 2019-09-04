#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint16_t ;
struct workqueue {scalar_t__ wq_thdying_count; int wq_thidlecount; } ;
struct TYPE_3__ {scalar_t__ idle_stamp; } ;
struct TYPE_4__ {TYPE_1__ uus_workq_park_data; } ;
struct uthread {TYPE_2__ uu_save; int /*<<< orphan*/  uu_workq_flags; } ;

/* Variables and functions */
 int DBG_FUNC_START ; 
 int TRACE_wq_thread_terminate ; 
 int /*<<< orphan*/  UT_WORKQ_DYING ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int,struct workqueue*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  workq_death_call_schedule (struct workqueue*,scalar_t__) ; 
 scalar_t__ workq_kill_delay_for_idle_thread (struct workqueue*) ; 
 struct uthread* workq_oldest_killable_idle_thread (struct workqueue*) ; 
 int /*<<< orphan*/  workq_thread_wakeup (struct uthread*) ; 

__attribute__((used)) static void
workq_death_policy_evaluate(struct workqueue *wq, uint16_t decrement)
{
	struct uthread *uth;

	assert(wq->wq_thdying_count >= decrement);
	if ((wq->wq_thdying_count -= decrement) > 0)
		return;

	if (wq->wq_thidlecount <= 1)
		return;

	if ((uth = workq_oldest_killable_idle_thread(wq)) == NULL)
		return;

	uint64_t now = mach_absolute_time();
	uint64_t delay = workq_kill_delay_for_idle_thread(wq);

	if (now - uth->uu_save.uus_workq_park_data.idle_stamp > delay) {
		WQ_TRACE_WQ(TRACE_wq_thread_terminate | DBG_FUNC_START,
				wq, wq->wq_thidlecount, 0, 0, 0);
		wq->wq_thdying_count++;
		uth->uu_workq_flags |= UT_WORKQ_DYING;
		workq_thread_wakeup(uth);
		return;
	}

	workq_death_call_schedule(wq,
			uth->uu_save.uus_workq_park_data.idle_stamp + delay);
}