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
struct qstr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; struct dentry* d_parent; scalar_t__ d_inode; } ;
struct autofs_wait_queue {int dummy; } ;
struct autofs_sb_info {scalar_t__ catatonic; int /*<<< orphan*/  wq_mutex; } ;
struct autofs_info {int flags; } ;
typedef  enum autofs_notify { ____Placeholder_autofs_notify } autofs_notify ;

/* Variables and functions */
 int AUTOFS_INF_EXPIRING ; 
 int EINTR ; 
 int ENOENT ; 
 int HZ ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 int NFY_MOUNT ; 
 int NFY_NONE ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 struct autofs_wait_queue* autofs4_find_wait (struct autofs_sb_info*,struct qstr*) ; 
 struct dentry* d_lookup (struct dentry*,int /*<<< orphan*/ *) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ have_submounts (struct dentry*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 

__attribute__((used)) static int validate_request(struct autofs_wait_queue **wait,
			    struct autofs_sb_info *sbi,
			    struct qstr *qstr,
			    struct dentry*dentry, enum autofs_notify notify)
{
	struct autofs_wait_queue *wq;
	struct autofs_info *ino;

	if (sbi->catatonic)
		return -ENOENT;

	/* Wait in progress, continue; */
	wq = autofs4_find_wait(sbi, qstr);
	if (wq) {
		*wait = wq;
		return 1;
	}

	*wait = NULL;

	/* If we don't yet have any info this is a new request */
	ino = autofs4_dentry_ino(dentry);
	if (!ino)
		return 1;

	/*
	 * If we've been asked to wait on an existing expire (NFY_NONE)
	 * but there is no wait in the queue ...
	 */
	if (notify == NFY_NONE) {
		/*
		 * Either we've betean the pending expire to post it's
		 * wait or it finished while we waited on the mutex.
		 * So we need to wait till either, the wait appears
		 * or the expire finishes.
		 */

		while (ino->flags & AUTOFS_INF_EXPIRING) {
			mutex_unlock(&sbi->wq_mutex);
			schedule_timeout_interruptible(HZ/10);
			if (mutex_lock_interruptible(&sbi->wq_mutex))
				return -EINTR;

			if (sbi->catatonic)
				return -ENOENT;

			wq = autofs4_find_wait(sbi, qstr);
			if (wq) {
				*wait = wq;
				return 1;
			}
		}

		/*
		 * Not ideal but the status has already gone. Of the two
		 * cases where we wait on NFY_NONE neither depend on the
		 * return status of the wait.
		 */
		return 0;
	}

	/*
	 * If we've been asked to trigger a mount and the request
	 * completed while we waited on the mutex ...
	 */
	if (notify == NFY_MOUNT) {
		struct dentry *new = NULL;
		int valid = 1;

		/*
		 * If the dentry was successfully mounted while we slept
		 * on the wait queue mutex we can return success. If it
		 * isn't mounted (doesn't have submounts for the case of
		 * a multi-mount with no mount at it's base) we can
		 * continue on and create a new request.
		 */
		if (!IS_ROOT(dentry)) {
			if (dentry->d_inode && d_unhashed(dentry)) {
				struct dentry *parent = dentry->d_parent;
				new = d_lookup(parent, &dentry->d_name);
				if (new)
					dentry = new;
			}
		}
		if (have_submounts(dentry))
			valid = 0;

		if (new)
			dput(new);
		return valid;
	}

	return 1;
}