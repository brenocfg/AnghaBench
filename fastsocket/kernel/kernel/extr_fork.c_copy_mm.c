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
struct task_struct {struct mm_struct* active_mm; struct mm_struct* mm; TYPE_1__* signal; scalar_t__ nivcsw; scalar_t__ nvcsw; scalar_t__ last_switch_count; scalar_t__ maj_flt; scalar_t__ min_flt; } ;
struct mm_struct {int /*<<< orphan*/  oom_disable_count; scalar_t__ last_interval; scalar_t__ token_priority; int /*<<< orphan*/  mm_users; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;
struct TYPE_3__ {scalar_t__ oom_score_adj; } ;

/* Variables and functions */
 unsigned long CLONE_VM ; 
 int ENOMEM ; 
 scalar_t__ OOM_SCORE_ADJ_MIN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 struct mm_struct* dup_mm (struct task_struct*) ; 

__attribute__((used)) static int copy_mm(unsigned long clone_flags, struct task_struct * tsk)
{
	struct mm_struct * mm, *oldmm;
	int retval;

	tsk->min_flt = tsk->maj_flt = 0;
	tsk->nvcsw = tsk->nivcsw = 0;
#ifdef CONFIG_DETECT_HUNG_TASK
	tsk->last_switch_count = tsk->nvcsw + tsk->nivcsw;
#endif

	tsk->mm = NULL;
	tsk->active_mm = NULL;

	/*
	 * Are we cloning a kernel thread?
	 *
	 * We need to steal a active VM for that..
	 */
	oldmm = current->mm;
	if (!oldmm)
		return 0;

	if (clone_flags & CLONE_VM) {
		atomic_inc(&oldmm->mm_users);
		mm = oldmm;
		goto good_mm;
	}

	retval = -ENOMEM;
	mm = dup_mm(tsk);
	if (!mm)
		goto fail_nomem;

good_mm:
	/* Initializing for Swap token stuff */
	mm->token_priority = 0;
	mm->last_interval = 0;
	if (tsk->signal->oom_score_adj == OOM_SCORE_ADJ_MIN)
		atomic_inc(&mm->oom_disable_count);

	tsk->mm = mm;
	tsk->active_mm = mm;
	return 0;

fail_nomem:
	return retval;
}