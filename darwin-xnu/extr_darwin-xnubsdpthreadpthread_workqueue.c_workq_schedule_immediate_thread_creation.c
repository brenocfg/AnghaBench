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
struct workqueue {int /*<<< orphan*/  wq_immediate_call; int /*<<< orphan*/  wq_reqcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_wq_start_add_timer ; 
 int /*<<< orphan*/  WQ_IMMEDIATE_CALL_PENDED ; 
 uintptr_t WQ_IMMEDIATE_CALL_SCHEDULED ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int /*<<< orphan*/ ,struct workqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _wq_flags (struct workqueue*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  preemption_enabled () ; 
 scalar_t__ thread_call_enter1 (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ workq_thread_call_prepost (struct workqueue*,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
workq_schedule_immediate_thread_creation(struct workqueue *wq)
{
	assert(!preemption_enabled());

	if (workq_thread_call_prepost(wq, WQ_IMMEDIATE_CALL_SCHEDULED,
			WQ_IMMEDIATE_CALL_PENDED, 0)) {
		WQ_TRACE_WQ(TRACE_wq_start_add_timer, wq, wq->wq_reqcount,
				_wq_flags(wq), 0, 0);

		uintptr_t arg = WQ_IMMEDIATE_CALL_SCHEDULED;
		if (thread_call_enter1(wq->wq_immediate_call, (void *)arg)) {
			panic("immediate_call was already enqueued");
		}
	}
}