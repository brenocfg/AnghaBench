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
struct linux_binprm {int /*<<< orphan*/  per_clear; int /*<<< orphan*/ * mm; int /*<<< orphan*/  file; } ;
struct TYPE_3__ {int /*<<< orphan*/  personality; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_RANDOMIZE ; 
 int /*<<< orphan*/  acct_arg_size (struct linux_binprm*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int de_thread (TYPE_1__*) ; 
 int exec_mmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_thread () ; 
 int /*<<< orphan*/  set_mm_exe_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int flush_old_exec(struct linux_binprm * bprm)
{
	int retval;

	/*
	 * Make sure we have a private signal table and that
	 * we are unassociated from the previous thread group.
	 */
	retval = de_thread(current);
	if (retval)
		goto out;

	set_mm_exe_file(bprm->mm, bprm->file);

	/*
	 * Release all of the old mmap stuff
	 */
	acct_arg_size(bprm, 0);
	retval = exec_mmap(bprm->mm);
	if (retval)
		goto out;

	bprm->mm = NULL;		/* We're using it now */

	current->flags &= ~PF_RANDOMIZE;
	flush_thread();
	current->personality &= ~bprm->per_clear;

	return 0;

out:
	return retval;
}