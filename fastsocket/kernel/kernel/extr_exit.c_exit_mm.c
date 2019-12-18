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
struct task_struct {TYPE_2__* signal; struct mm_struct* mm; struct mm_struct* active_mm; } ;
struct mm_struct {int /*<<< orphan*/  oom_disable_count; int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  mm_count; struct core_state* core_state; } ;
struct core_thread {struct task_struct* task; int /*<<< orphan*/  next; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
struct core_state {int /*<<< orphan*/  startup; int /*<<< orphan*/  nr_threads; TYPE_1__ dumper; } ;
struct TYPE_4__ {scalar_t__ oom_score_adj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OOM_SCORE_ADJ_MIN ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_task_state (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_freeze_flag (struct task_struct*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enter_lazy_tlb (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_release (struct task_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  mm_update_next_owner (struct mm_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_task_state (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,struct core_thread*) ; 

__attribute__((used)) static void exit_mm(struct task_struct * tsk)
{
	struct mm_struct *mm = tsk->mm;
	struct core_state *core_state;

	mm_release(tsk, mm);
	if (!mm)
		return;
	/*
	 * Serialize with any possible pending coredump.
	 * We must hold mmap_sem around checking core_state
	 * and clearing tsk->mm.  The core-inducing thread
	 * will increment ->nr_threads for each thread in the
	 * group with ->mm != NULL.
	 */
	down_read(&mm->mmap_sem);
	core_state = mm->core_state;
	if (core_state) {
		struct core_thread self;
		up_read(&mm->mmap_sem);

		self.task = tsk;
		self.next = xchg(&core_state->dumper.next, &self);
		/*
		 * Implies mb(), the result of xchg() must be visible
		 * to core_state->dumper.
		 */
		if (atomic_dec_and_test(&core_state->nr_threads))
			complete(&core_state->startup);

		for (;;) {
			set_task_state(tsk, TASK_UNINTERRUPTIBLE);
			if (!self.task) /* see coredump_finish() */
				break;
			schedule();
		}
		__set_task_state(tsk, TASK_RUNNING);
		down_read(&mm->mmap_sem);
	}
	atomic_inc(&mm->mm_count);
	BUG_ON(mm != tsk->active_mm);
	/* more a memory barrier than a real lock */
	task_lock(tsk);
	tsk->mm = NULL;
	up_read(&mm->mmap_sem);
	enter_lazy_tlb(mm, current);
	/* We don't want this task to be frozen prematurely */
	clear_freeze_flag(tsk);
	if (tsk->signal->oom_score_adj == OOM_SCORE_ADJ_MIN)
		atomic_dec(&mm->oom_disable_count);
	task_unlock(tsk);
	mm_update_next_owner(mm);
	mmput(mm);
}