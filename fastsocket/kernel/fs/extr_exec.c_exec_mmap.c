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
struct task_struct {struct mm_struct* mm; TYPE_1__* signal; struct mm_struct* active_mm; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/  oom_disable_count; int /*<<< orphan*/  core_state; } ;
struct TYPE_2__ {scalar_t__ oom_score_adj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINTR ; 
 scalar_t__ OOM_SCORE_ADJ_MIN ; 
 int /*<<< orphan*/  activate_mm (struct mm_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  arch_pick_mmap_layout (struct mm_struct*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_release (struct task_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  mm_update_next_owner (struct mm_struct*) ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exec_mmap(struct mm_struct *mm)
{
	struct task_struct *tsk;
	struct mm_struct * old_mm, *active_mm;

	/* Notify parent that we're no longer interested in the old VM */
	tsk = current;
	old_mm = current->mm;
	mm_release(tsk, old_mm);

	if (old_mm) {
		/*
		 * Make sure that if there is a core dump in progress
		 * for the old mm, we get out and die instead of going
		 * through with the exec.  We must hold mmap_sem around
		 * checking core_state and changing tsk->mm.
		 */
		down_read(&old_mm->mmap_sem);
		if (unlikely(old_mm->core_state)) {
			up_read(&old_mm->mmap_sem);
			return -EINTR;
		}
	}
	task_lock(tsk);
	active_mm = tsk->active_mm;
	tsk->mm = mm;
	tsk->active_mm = mm;
	activate_mm(active_mm, mm);
	if (old_mm && tsk->signal->oom_score_adj == OOM_SCORE_ADJ_MIN) {
		atomic_dec(&old_mm->oom_disable_count);
		atomic_inc(&tsk->mm->oom_disable_count);
	}
	task_unlock(tsk);
	arch_pick_mmap_layout(mm);
	if (old_mm) {
		up_read(&old_mm->mmap_sem);
		BUG_ON(active_mm != old_mm);
		mm_update_next_owner(old_mm);
		mmput(old_mm);
		return 0;
	}
	mmdrop(active_mm);
	return 0;
}