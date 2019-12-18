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
struct task_struct {struct mm_struct* active_mm; struct mm_struct* mm; } ;
struct TYPE_2__ {int alloc_pgste; scalar_t__ has_pgste; } ;
struct mm_struct {int /*<<< orphan*/  ioctx_list; int /*<<< orphan*/  mm_users; TYPE_1__ context; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ HOME_SPACE_MODE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 struct mm_struct* dup_mm (struct task_struct*) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  update_mm (struct mm_struct*,struct task_struct*) ; 
 scalar_t__ user_mode ; 

int s390_enable_sie(void)
{
	struct task_struct *tsk = current;
	struct mm_struct *mm, *old_mm;

	/* Do we have switched amode? If no, we cannot do sie */
	if (user_mode == HOME_SPACE_MODE)
		return -EINVAL;

	/* Do we have pgstes? if yes, we are done */
	if (tsk->mm->context.has_pgste)
		return 0;

	/* lets check if we are allowed to replace the mm */
	task_lock(tsk);
	if (!tsk->mm || atomic_read(&tsk->mm->mm_users) > 1 ||
#ifdef CONFIG_AIO
	    !hlist_empty(&tsk->mm->ioctx_list) ||
#endif
	    tsk->mm != tsk->active_mm) {
		task_unlock(tsk);
		return -EINVAL;
	}
	task_unlock(tsk);

	/* we copy the mm and let dup_mm create the page tables with_pgstes */
	tsk->mm->context.alloc_pgste = 1;
	mm = dup_mm(tsk);
	tsk->mm->context.alloc_pgste = 0;
	if (!mm)
		return -ENOMEM;

	/* Now lets check again if something happened */
	task_lock(tsk);
	if (!tsk->mm || atomic_read(&tsk->mm->mm_users) > 1 ||
#ifdef CONFIG_AIO
	    !hlist_empty(&tsk->mm->ioctx_list) ||
#endif
	    tsk->mm != tsk->active_mm) {
		mmput(mm);
		task_unlock(tsk);
		return -EINVAL;
	}

	/* ok, we are alone. No ptrace, no threads, etc. */
	old_mm = tsk->mm;
	tsk->mm = tsk->active_mm = mm;
	preempt_disable();
	update_mm(mm, tsk);
	cpumask_set_cpu(smp_processor_id(), mm_cpumask(mm));
	preempt_enable();
	task_unlock(tsk);
	mmput(old_mm);
	return 0;
}