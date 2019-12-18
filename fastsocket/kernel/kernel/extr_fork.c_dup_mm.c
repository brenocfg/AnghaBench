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
struct task_struct {int dummy; } ;
struct mm_struct {TYPE_1__* binfmt; int /*<<< orphan*/  total_vm; int /*<<< orphan*/  hiwater_vm; int /*<<< orphan*/  hiwater_rss; int /*<<< orphan*/ * pmd_huge_pte; scalar_t__ last_interval; scalar_t__ token_priority; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 struct mm_struct* allocate_mm () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dup_mm_exe_file (struct mm_struct*,struct mm_struct*) ; 
 int dup_mmap (struct mm_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  free_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  get_mm_rss (struct mm_struct*) ; 
 scalar_t__ init_new_context (struct task_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  memcpy (struct mm_struct*,struct mm_struct*,int) ; 
 int /*<<< orphan*/  mm_free_pgd (struct mm_struct*) ; 
 int /*<<< orphan*/  mm_init (struct mm_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct mm_struct *dup_mm(struct task_struct *tsk)
{
	struct mm_struct *mm, *oldmm = current->mm;
	int err;

	if (!oldmm)
		return NULL;

	mm = allocate_mm();
	if (!mm)
		goto fail_nomem;

	memcpy(mm, oldmm, sizeof(*mm));

	/* Initializing for Swap token stuff */
	mm->token_priority = 0;
	mm->last_interval = 0;

#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	mm->pmd_huge_pte = NULL;
#endif

	if (!mm_init(mm, tsk))
		goto fail_nomem;

	if (init_new_context(tsk, mm))
		goto fail_nocontext;

	dup_mm_exe_file(oldmm, mm);

	err = dup_mmap(mm, oldmm);
	if (err)
		goto free_pt;

	mm->hiwater_rss = get_mm_rss(mm);
	mm->hiwater_vm = mm->total_vm;

	if (mm->binfmt && !try_module_get(mm->binfmt->module))
		goto free_pt;

	return mm;

free_pt:
	/* don't put binfmt in mmput, we haven't got module yet */
	mm->binfmt = NULL;
	mmput(mm);

fail_nomem:
	return NULL;

fail_nocontext:
	/*
	 * If init_new_context() failed, we cannot use mmput() to free the mm
	 * because it calls destroy_context()
	 */
	mm_free_pgd(mm);
	free_mm(mm);
	return NULL;
}