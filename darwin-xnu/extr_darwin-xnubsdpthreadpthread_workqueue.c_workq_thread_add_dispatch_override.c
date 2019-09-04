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
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ thread_t ;
typedef  scalar_t__ thread_qos_t ;
struct workqueue {int dummy; } ;
struct uu_workq_policy {scalar_t__ qos_override; } ;
struct uthread {struct uu_workq_policy uu_workq_pri; } ;
typedef  int /*<<< orphan*/  pthread_priority_t ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  scalar_t__ mach_port_name_t ;
typedef  int /*<<< orphan*/  kport ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 scalar_t__ THREAD_NULL ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int THREAD_TAG_WORKQUEUE ; 
 int TRACE_wq_override_dispatch ; 
 int /*<<< orphan*/  WQ_TRACE_WQ (int,struct workqueue*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _pthread_priority_thread_qos (int /*<<< orphan*/ ) ; 
 int copyin_word (scalar_t__,scalar_t__*,int) ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 struct uthread* get_bsdthread_info (scalar_t__) ; 
 scalar_t__ port_name_to_thread (scalar_t__) ; 
 struct workqueue* proc_get_wqptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_deallocate (scalar_t__) ; 
 int thread_get_tag (scalar_t__) ; 
 int /*<<< orphan*/  thread_mtx_lock (scalar_t__) ; 
 int /*<<< orphan*/  thread_mtx_unlock (scalar_t__) ; 
 int /*<<< orphan*/  thread_set_workq_override (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  thread_tid (scalar_t__) ; 
 scalar_t__ ulock_owner_value_to_port_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_lock_spin (struct workqueue*) ; 
 scalar_t__ workq_pri_override (struct uu_workq_policy) ; 
 int /*<<< orphan*/  workq_thread_update_bucket (int /*<<< orphan*/ ,struct workqueue*,struct uthread*,struct uu_workq_policy,struct uu_workq_policy,int) ; 
 int /*<<< orphan*/  workq_unlock (struct workqueue*) ; 

__attribute__((used)) static int
workq_thread_add_dispatch_override(proc_t p, mach_port_name_t kport,
		pthread_priority_t pp, user_addr_t ulock_addr)
{
	struct uu_workq_policy old_pri, new_pri;
	struct workqueue *wq = proc_get_wqptr(p);

	thread_qos_t qos_override = _pthread_priority_thread_qos(pp);
	if (qos_override == THREAD_QOS_UNSPECIFIED) {
		return EINVAL;
	}

	thread_t thread = port_name_to_thread(kport);
	if (thread == THREAD_NULL) {
		return ESRCH;
	}

	struct uthread *uth = get_bsdthread_info(thread);
	if ((thread_get_tag(thread) & THREAD_TAG_WORKQUEUE) == 0) {
		thread_deallocate(thread);
		return EPERM;
	}

	WQ_TRACE_WQ(TRACE_wq_override_dispatch | DBG_FUNC_NONE,
			wq, thread_tid(thread), 1, pp, 0);

	thread_mtx_lock(thread);

	if (ulock_addr) {
		uint64_t val;
		int rc;
		/*
		 * Workaround lack of explicit support for 'no-fault copyin'
		 * <rdar://problem/24999882>, as disabling preemption prevents paging in
		 */
		disable_preemption();
		rc = copyin_word(ulock_addr, &val, sizeof(kport));
		enable_preemption();
		if (rc == 0 && ulock_owner_value_to_port_name((uint32_t)val) != kport) {
			goto out;
		}
	}

	workq_lock_spin(wq);

	old_pri = uth->uu_workq_pri;
	if (old_pri.qos_override >= qos_override) {
		/* Nothing to do */
	} else if (thread == current_thread()) {
		new_pri = old_pri;
		new_pri.qos_override = qos_override;
		workq_thread_update_bucket(p, wq, uth, old_pri, new_pri, false);
	} else {
		uth->uu_workq_pri.qos_override = qos_override;
		if (qos_override > workq_pri_override(old_pri)) {
			thread_set_workq_override(thread, qos_override);
		}
	}

	workq_unlock(wq);

out:
	thread_mtx_unlock(thread);
	thread_deallocate(thread);
	return 0;
}