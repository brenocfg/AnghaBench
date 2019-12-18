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
struct ocfs2_mask_waiter {int dummy; } ;
struct ocfs2_lock_res {int l_flags; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_name; } ;

/* Variables and functions */
 int OCFS2_LOCK_FREEING ; 
 int OCFS2_LOCK_QUEUED ; 
 int /*<<< orphan*/  lockres_add_mask_waiter (struct ocfs2_lock_res*,struct ocfs2_mask_waiter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_init_mask_waiter (struct ocfs2_mask_waiter*) ; 
 int ocfs2_wait_for_mask (struct ocfs2_mask_waiter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ocfs2_mark_lockres_freeing(struct ocfs2_lock_res *lockres)
{
	int status;
	struct ocfs2_mask_waiter mw;
	unsigned long flags;

	ocfs2_init_mask_waiter(&mw);

	spin_lock_irqsave(&lockres->l_lock, flags);
	lockres->l_flags |= OCFS2_LOCK_FREEING;
	while (lockres->l_flags & OCFS2_LOCK_QUEUED) {
		lockres_add_mask_waiter(lockres, &mw, OCFS2_LOCK_QUEUED, 0);
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		mlog(0, "Waiting on lockres %s\n", lockres->l_name);

		status = ocfs2_wait_for_mask(&mw);
		if (status)
			mlog_errno(status);

		spin_lock_irqsave(&lockres->l_lock, flags);
	}
	spin_unlock_irqrestore(&lockres->l_lock, flags);
}