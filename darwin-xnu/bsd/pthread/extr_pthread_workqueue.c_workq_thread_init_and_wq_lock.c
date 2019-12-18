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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  task_t ;
struct uthread {scalar_t__ uu_workq_stackaddr; int /*<<< orphan*/  uu_workq_thport; int /*<<< orphan*/  uu_workq_pri; int /*<<< orphan*/  uu_workq_flags; } ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  THREAD_QOS_LEGACY ; 
 int THREAD_TAG_PTHREAD ; 
 int THREAD_TAG_WORKQUEUE ; 
 int /*<<< orphan*/  UT_WORKQ_NEW ; 
 int /*<<< orphan*/  WORKQ_POLICY_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bsdtask_info (int /*<<< orphan*/ ) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_get_wqptr_fast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_reset_workq_qos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_tag (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  workq_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_parked_wait_event (struct uthread*) ; 

event_t
workq_thread_init_and_wq_lock(task_t task, thread_t th)
{
	struct uthread *uth = get_bsdthread_info(th);

	uth->uu_workq_flags = UT_WORKQ_NEW;
	uth->uu_workq_pri = WORKQ_POLICY_INIT(THREAD_QOS_LEGACY);
	uth->uu_workq_thport = MACH_PORT_NULL;
	uth->uu_workq_stackaddr = 0;

	thread_set_tag(th, THREAD_TAG_PTHREAD | THREAD_TAG_WORKQUEUE);
	thread_reset_workq_qos(th, THREAD_QOS_LEGACY);

	workq_lock_spin(proc_get_wqptr_fast(get_bsdtask_info(task)));
	return workq_parked_wait_event(uth);
}