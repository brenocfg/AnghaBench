#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* task_t ;
struct kperf_task_snapshot {int /*<<< orphan*/  kptksn_system_time_in_terminated_threads; int /*<<< orphan*/  kptksn_user_time_in_terminated_threads; int /*<<< orphan*/  kptksn_pageins; int /*<<< orphan*/  kptksn_suspend_count; int /*<<< orphan*/  kptksn_flags; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {scalar_t__ trp_role; int trp_boosted; } ;
struct TYPE_5__ {scalar_t__ tep_darwinbg; } ;
struct TYPE_7__ {int /*<<< orphan*/  total_system_time; int /*<<< orphan*/  total_user_time; int /*<<< orphan*/  pageins; int /*<<< orphan*/  suspend_count; int /*<<< orphan*/  bsd_info; TYPE_2__ requested_policy; TYPE_1__ effective_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int) ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KPERF_TASK_ALLOW_IDLE_EXIT ; 
 int /*<<< orphan*/  KPERF_TASK_FLAG_BOOSTED ; 
 int /*<<< orphan*/  KPERF_TASK_FLAG_DARWIN_BG ; 
 int /*<<< orphan*/  KPERF_TASK_FLAG_DIRTY ; 
 int /*<<< orphan*/  KPERF_TASK_FLAG_DIRTY_TRACKED ; 
 int /*<<< orphan*/  KPERF_TASK_FLAG_FOREGROUND ; 
 int PERF_TK_SNAP_SAMPLE ; 
 scalar_t__ TASK_FOREGROUND_APPLICATION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memorystatus_proc_flags_unsafe (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 

void
kperf_task_snapshot_sample(task_t task, struct kperf_task_snapshot *tksn)
{
	BUF_INFO(PERF_TK_SNAP_SAMPLE | DBG_FUNC_START);

	assert(tksn != NULL);

	tksn->kptksn_flags = 0;
	if (task->effective_policy.tep_darwinbg) {
		tksn->kptksn_flags |= KPERF_TASK_FLAG_DARWIN_BG;
	}
	if (task->requested_policy.trp_role == TASK_FOREGROUND_APPLICATION) {
		tksn->kptksn_flags |= KPERF_TASK_FLAG_FOREGROUND;
	}
	if (task->requested_policy.trp_boosted == 1) {
		tksn->kptksn_flags |= KPERF_TASK_FLAG_BOOSTED;
	}
#if CONFIG_MEMORYSTATUS
	boolean_t dirty = FALSE, dirty_tracked = FALSE, allow_idle_exit = FALSE;
	memorystatus_proc_flags_unsafe(task->bsd_info, &dirty, &dirty_tracked, &allow_idle_exit);
	if (dirty) {
		tksn->kptksn_flags |= KPERF_TASK_FLAG_DIRTY;
	}
	if (dirty_tracked) {
		tksn->kptksn_flags |= KPERF_TASK_FLAG_DIRTY_TRACKED;
	}
	if (allow_idle_exit) {
		tksn->kptksn_flags |= KPERF_TASK_ALLOW_IDLE_EXIT;
	}
#endif

	tksn->kptksn_suspend_count = task->suspend_count;
	tksn->kptksn_pageins = task->pageins;
	tksn->kptksn_user_time_in_terminated_threads = task->total_user_time;
	tksn->kptksn_system_time_in_terminated_threads = task->total_system_time;

	BUF_INFO(PERF_TK_SNAP_SAMPLE | DBG_FUNC_END);
}