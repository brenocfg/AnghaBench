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
struct nfs_open_context {int dummy; } ;
struct nfs4_state {struct inode* inode; } ;
struct inode {struct file_lock* i_flock; } ;
struct file_lock {int fl_flags; int /*<<< orphan*/  fl_file; struct file_lock* fl_next; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int FL_FLOCK ; 
 int FL_POSIX ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int nfs4_lock_delegation_recall (struct file_lock*,struct nfs4_state*,int /*<<< orphan*/  const*) ; 
 struct nfs_open_context* nfs_file_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int nfs_delegation_claim_locks(struct nfs_open_context *ctx, struct nfs4_state *state, const nfs4_stateid *stateid)
{
	struct inode *inode = state->inode;
	struct file_lock *fl;
	int status = 0;

	if (inode->i_flock == NULL)
		return 0;

	if (inode->i_flock == NULL)
		goto out;
	/* Protect inode->i_flock using the BKL */
	lock_kernel();
	for (fl = inode->i_flock; fl != NULL; fl = fl->fl_next) {
		if (!(fl->fl_flags & (FL_POSIX|FL_FLOCK)))
			continue;
		if (nfs_file_open_context(fl->fl_file) != ctx)
			continue;
		unlock_kernel();
		status = nfs4_lock_delegation_recall(fl, state, stateid);
		if (status < 0)
			goto out;
		lock_kernel();
	}
	unlock_kernel();
out:
	return status;
}