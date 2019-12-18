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
struct workqueue {int dummy; } ;
struct uu_workq_policy {int /*<<< orphan*/  qos_override; } ;
struct uthread {struct uu_workq_policy uu_workq_pri; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int EPERM ; 
 int /*<<< orphan*/  THREAD_QOS_UNSPECIFIED ; 
 int THREAD_TAG_WORKQUEUE ; 
 int TRACE_wq_override_reset ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int,struct workqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 struct workqueue* proc_get_wqptr (int /*<<< orphan*/ ) ; 
 int thread_get_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_lock_spin (struct workqueue*) ; 
 int /*<<< orphan*/  workq_thread_update_bucket (int /*<<< orphan*/ ,struct workqueue*,struct uthread*,struct uu_workq_policy,struct uu_workq_policy,int) ; 
 int /*<<< orphan*/  workq_unlock (struct workqueue*) ; 

__attribute__((used)) static int
workq_thread_reset_dispatch_override(proc_t p, thread_t thread)
{
	struct uu_workq_policy old_pri, new_pri;
	struct workqueue *wq = proc_get_wqptr(p);
	struct uthread *uth = get_bsdthread_info(thread);

	if ((thread_get_tag(thread) & THREAD_TAG_WORKQUEUE) == 0) {
		return EPERM;
	}

	WQ_TRACE_WQ(TRACE_wq_override_reset | DBG_FUNC_NONE, wq, 0, 0, 0, 0);

	workq_lock_spin(wq);
	old_pri = new_pri = uth->uu_workq_pri;
	new_pri.qos_override = THREAD_QOS_UNSPECIFIED;
	workq_thread_update_bucket(p, wq, uth, old_pri, new_pri, false);
	workq_unlock(wq);
	return 0;
}