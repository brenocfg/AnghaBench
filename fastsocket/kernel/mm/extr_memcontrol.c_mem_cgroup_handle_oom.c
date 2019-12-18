#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  task_list; int /*<<< orphan*/  private; int /*<<< orphan*/  func; scalar_t__ flags; } ;
struct oom_wait_info {TYPE_1__ wait; struct mem_cgroup* mem; } ;
struct mem_cgroup {scalar_t__ oom_kill_disable; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  TIF_MEMDIE ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mem_cgroup_mark_under_oom (struct mem_cgroup*) ; 
 int mem_cgroup_oom_lock (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_oom_notify (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_oom_unlock (struct mem_cgroup*) ; 
 int /*<<< orphan*/  mem_cgroup_out_of_memory (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_unmark_under_oom (struct mem_cgroup*) ; 
 int /*<<< orphan*/  memcg_oom_lock ; 
 int /*<<< orphan*/  memcg_oom_waitq ; 
 int /*<<< orphan*/  memcg_oom_wake_function ; 
 int /*<<< orphan*/  memcg_wakeup_oom (struct mem_cgroup*) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

bool mem_cgroup_handle_oom(struct mem_cgroup *mem, gfp_t mask)
{
	struct oom_wait_info owait;
	bool locked, need_to_kill;

	owait.mem = mem;
	owait.wait.flags = 0;
	owait.wait.func = memcg_oom_wake_function;
	owait.wait.private = current;
	INIT_LIST_HEAD(&owait.wait.task_list);
	need_to_kill = true;
	mem_cgroup_mark_under_oom(mem);

	/* At first, try to OOM lock hierarchy under mem.*/
	spin_lock(&memcg_oom_lock);
	locked = mem_cgroup_oom_lock(mem);
	/*
	 * Even if signal_pending(), we can't quit charge() loop without
	 * accounting. So, UNINTERRUPTIBLE is appropriate. But SIGKILL
	 * under OOM is always welcomed, use TASK_KILLABLE here.
	 */
	prepare_to_wait(&memcg_oom_waitq, &owait.wait, TASK_KILLABLE);
	if (!locked || mem->oom_kill_disable)
		need_to_kill = false;
	if (locked)
		mem_cgroup_oom_notify(mem);
	spin_unlock(&memcg_oom_lock);

	if (need_to_kill) {
		finish_wait(&memcg_oom_waitq, &owait.wait);
		mem_cgroup_out_of_memory(mem, mask);
	} else {
		schedule();
		finish_wait(&memcg_oom_waitq, &owait.wait);
	}
	spin_lock(&memcg_oom_lock);
	if (locked)
		mem_cgroup_oom_unlock(mem);
	memcg_wakeup_oom(mem);
	spin_unlock(&memcg_oom_lock);

	mem_cgroup_unmark_under_oom(mem);

	if (test_thread_flag(TIF_MEMDIE) || fatal_signal_pending(current))
		return false;
	/* Give chance to dying process */
	schedule_timeout_uninterruptible(1);
	return true;
}