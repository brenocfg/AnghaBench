#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
struct file {struct dlm_user_proc* private_data; } ;
struct dlm_user_proc {int /*<<< orphan*/  flags; int /*<<< orphan*/  lockspace; } ;
struct dlm_ls {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_PROC_FLAGS_CLOSING ; 
 int ENOENT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  dlm_clear_proc_locks (struct dlm_ls*,struct dlm_user_proc*) ; 
 struct dlm_ls* dlm_find_lockspace_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int /*<<< orphan*/  kfree (struct dlm_user_proc*) ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int device_close(struct inode *inode, struct file *file)
{
	struct dlm_user_proc *proc = file->private_data;
	struct dlm_ls *ls;
	sigset_t tmpsig, allsigs;

	ls = dlm_find_lockspace_local(proc->lockspace);
	if (!ls)
		return -ENOENT;

	sigfillset(&allsigs);
	sigprocmask(SIG_BLOCK, &allsigs, &tmpsig);

	set_bit(DLM_PROC_FLAGS_CLOSING, &proc->flags);

	dlm_clear_proc_locks(ls, proc);

	/* at this point no more lkb's should exist for this lockspace,
	   so there's no chance of dlm_user_add_ast() being called and
	   looking for lkb->ua->proc */

	kfree(proc);
	file->private_data = NULL;

	dlm_put_lockspace(ls);
	dlm_put_lockspace(ls);  /* for the find in device_open() */

	/* FIXME: AUTOFREE: if this ls is no longer used do
	   device_remove_lockspace() */

	sigprocmask(SIG_SETMASK, &tmpsig, NULL);
	recalc_sigpending();

	return 0;
}