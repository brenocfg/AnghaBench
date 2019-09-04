#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* unaligned_u64 ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_3__* thread_t ;
struct thread_delta_snapshot_v3 {void* tds_effective_policy; void* tds_requested_policy; scalar_t__ tds_io_tier; int /*<<< orphan*/  tds_rqos_override; int /*<<< orphan*/  tds_rqos; int /*<<< orphan*/  tds_eqos; int /*<<< orphan*/  tds_sched_priority; int /*<<< orphan*/  tds_base_priority; int /*<<< orphan*/  tds_sched_flags; int /*<<< orphan*/  tds_state; int /*<<< orphan*/  tds_last_made_runnable_time; int /*<<< orphan*/  tds_ss_flags; scalar_t__ tds_voucher_identifier; int /*<<< orphan*/  tds_thread_id; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  thep_qos; scalar_t__ thep_darwinbg; } ;
struct TYPE_8__ {int /*<<< orphan*/  thrp_qos_workq_override; int /*<<< orphan*/  thrp_qos_override; int /*<<< orphan*/  thrp_qos; } ;
struct TYPE_10__ {scalar_t__ ith_voucher; scalar_t__ suspend_count; int options; TYPE_2__ effective_policy; TYPE_1__ requested_policy; int /*<<< orphan*/  sched_pri; int /*<<< orphan*/  base_pri; int /*<<< orphan*/  sched_flags; int /*<<< orphan*/  state; int /*<<< orphan*/  last_made_runnable_time; } ;

/* Variables and functions */
 scalar_t__ IPC_VOUCHER_NULL ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_POLICY_IO ; 
 int /*<<< orphan*/  TASK_POLICY_PASSIVE_IO ; 
 int TH_OPT_GLOBAL_FORCED_IDLE ; 
 scalar_t__ VM_KERNEL_ADDRPERM (scalar_t__) ; 
 int /*<<< orphan*/  kGlobalForcedIdle ; 
 int /*<<< orphan*/  kThreadDarwinBG ; 
 int /*<<< orphan*/  kThreadIOPassive ; 
 int /*<<< orphan*/  kThreadIdleWorker ; 
 int /*<<< orphan*/  kThreadOnCore ; 
 int /*<<< orphan*/  kThreadSuspended ; 
 scalar_t__ proc_get_effective_thread_policy (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stackshot_thread_is_idle_worker_unsafe (TYPE_3__*) ; 
 int /*<<< orphan*/  static_assert (int) ; 
 int /*<<< orphan*/  thread_tid (TYPE_3__*) ; 

__attribute__((used)) static int
kcdata_record_thread_delta_snapshot(struct thread_delta_snapshot_v3 * cur_thread_snap, thread_t thread, boolean_t thread_on_core)
{
	cur_thread_snap->tds_thread_id = thread_tid(thread);
	if (IPC_VOUCHER_NULL != thread->ith_voucher)
		cur_thread_snap->tds_voucher_identifier  = VM_KERNEL_ADDRPERM(thread->ith_voucher);
	else
		cur_thread_snap->tds_voucher_identifier = 0;

	cur_thread_snap->tds_ss_flags = 0;
	if (thread->effective_policy.thep_darwinbg)
		cur_thread_snap->tds_ss_flags |= kThreadDarwinBG;
	if (proc_get_effective_thread_policy(thread, TASK_POLICY_PASSIVE_IO))
		cur_thread_snap->tds_ss_flags |= kThreadIOPassive;
	if (thread->suspend_count > 0)
		cur_thread_snap->tds_ss_flags |= kThreadSuspended;
	if (thread->options & TH_OPT_GLOBAL_FORCED_IDLE)
		cur_thread_snap->tds_ss_flags |= kGlobalForcedIdle;
	if (thread_on_core)
		cur_thread_snap->tds_ss_flags |= kThreadOnCore;
	if (stackshot_thread_is_idle_worker_unsafe(thread))
		cur_thread_snap->tds_ss_flags |= kThreadIdleWorker;

	cur_thread_snap->tds_last_made_runnable_time = thread->last_made_runnable_time;
	cur_thread_snap->tds_state                   = thread->state;
	cur_thread_snap->tds_sched_flags             = thread->sched_flags;
	cur_thread_snap->tds_base_priority           = thread->base_pri;
	cur_thread_snap->tds_sched_priority          = thread->sched_pri;
	cur_thread_snap->tds_eqos                    = thread->effective_policy.thep_qos;
	cur_thread_snap->tds_rqos                    = thread->requested_policy.thrp_qos;
	cur_thread_snap->tds_rqos_override           = MAX(thread->requested_policy.thrp_qos_override,
													   thread->requested_policy.thrp_qos_workq_override);
	cur_thread_snap->tds_io_tier                 = proc_get_effective_thread_policy(thread, TASK_POLICY_IO);

	static_assert(sizeof(thread->effective_policy) == sizeof(uint64_t));
	static_assert(sizeof(thread->requested_policy) == sizeof(uint64_t));
	cur_thread_snap->tds_requested_policy = *(unaligned_u64 *) &thread->requested_policy;
	cur_thread_snap->tds_effective_policy = *(unaligned_u64 *) &thread->effective_policy;

	return 0;
}