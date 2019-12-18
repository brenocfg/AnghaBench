#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zonelist {int dummy; } ;
struct task_struct {TYPE_1__* mm; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum oom_constraint { ____Placeholder_oom_constraint } oom_constraint ;
struct TYPE_2__ {int /*<<< orphan*/  oom_disable_count; } ;

/* Variables and functions */
 int CONSTRAINT_MEMORY_POLICY ; 
 int CONSTRAINT_NONE ; 
 unsigned long PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  TIF_MEMDIE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  check_panic_on_oom (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int constrained_alloc (struct zonelist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  dump_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ fatal_signal_pending (struct task_struct*) ; 
 scalar_t__ oom_kill_process (struct task_struct*,int /*<<< orphan*/ ,int,unsigned int,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  oom_notify_list ; 
 int /*<<< orphan*/  oom_unkillable_task (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 struct task_struct* select_bad_process (unsigned int*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_oom_kill_allocating_task ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

void out_of_memory(struct zonelist *zonelist, gfp_t gfp_mask,
		int order, nodemask_t *nodemask)
{
	const nodemask_t *mpol_mask;
	struct task_struct *p;
	unsigned long totalpages;
	unsigned long freed = 0;
	unsigned int points;
	enum oom_constraint constraint = CONSTRAINT_NONE;
	int killed = 0;

	blocking_notifier_call_chain(&oom_notify_list, 0, &freed);
	if (freed > 0)
		/* Got some memory back in the last second. */
		return;

	/*
	 * If current has a pending SIGKILL, then automatically select it.  The
	 * goal is to allow it to allocate so that it may quickly exit and free
	 * its memory.
	 */
	if (fatal_signal_pending(current)) {
		set_thread_flag(TIF_MEMDIE);
		return;
	}

	/*
	 * Check if there were limitations on the allocation (only relevant for
	 * NUMA) that may require different handling.
	 */
	constraint = constrained_alloc(zonelist, gfp_mask, nodemask,
						&totalpages);
	mpol_mask = (constraint == CONSTRAINT_MEMORY_POLICY) ? nodemask : NULL;
	check_panic_on_oom(constraint, gfp_mask, order, mpol_mask);

	read_lock(&tasklist_lock);
	if (sysctl_oom_kill_allocating_task &&
	    !oom_unkillable_task(current, NULL, nodemask) &&
	    current->mm && !atomic_read(&current->mm->oom_disable_count)) {
		/*
		 * oom_kill_process() needs tasklist_lock held.  If it returns
		 * non-zero, current could not be killed so we must fallback to
		 * the tasklist scan.
		 */
		if (!oom_kill_process(current, gfp_mask, order, 0, totalpages,
				NULL, nodemask,
				"Out of memory (oom_kill_allocating_task)"))
			goto out;
	}

retry:
	p = select_bad_process(&points, totalpages, NULL, mpol_mask);
	if (PTR_ERR(p) == -1UL)
		goto out;

	/* Found nothing?!?! Either we hang forever, or we panic. */
	if (!p) {
		dump_header(NULL, gfp_mask, order, NULL, mpol_mask);
		read_unlock(&tasklist_lock);
		panic("Out of memory and no killable processes...\n");
	}

	if (oom_kill_process(p, gfp_mask, order, points, totalpages, NULL,
				nodemask, "Out of memory"))
		goto retry;
	killed = 1;
out:
	read_unlock(&tasklist_lock);

	/*
	 * Give "p" a good chance of killing itself before we
	 * retry to allocate memory unless "p" is current
	 */
	if (killed && !test_thread_flag(TIF_MEMDIE))
		schedule_timeout_uninterruptible(1);
}