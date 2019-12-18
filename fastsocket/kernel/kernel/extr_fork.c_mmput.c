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
struct mm_struct {TYPE_1__* binfmt; int /*<<< orphan*/  mmlist; int /*<<< orphan*/  mm_users; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_aio (struct mm_struct*) ; 
 int /*<<< orphan*/  exit_mmap (struct mm_struct*) ; 
 int /*<<< orphan*/  khugepaged_exit (struct mm_struct*) ; 
 int /*<<< orphan*/  ksm_exit (struct mm_struct*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  mmlist_lock ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_swap_token (struct mm_struct*) ; 
 int /*<<< orphan*/  set_mm_exe_file (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mmput(struct mm_struct *mm)
{
	might_sleep();

	if (atomic_dec_and_test(&mm->mm_users)) {
		exit_aio(mm);
		ksm_exit(mm);
		khugepaged_exit(mm); /* must run before exit_mmap */
		exit_mmap(mm);
		set_mm_exe_file(mm, NULL);
		if (!list_empty(&mm->mmlist)) {
			spin_lock(&mmlist_lock);
			list_del(&mm->mmlist);
			spin_unlock(&mmlist_lock);
		}
		put_swap_token(mm);
		if (mm->binfmt)
			module_put(mm->binfmt->module);
		mmdrop(mm);
	}
}