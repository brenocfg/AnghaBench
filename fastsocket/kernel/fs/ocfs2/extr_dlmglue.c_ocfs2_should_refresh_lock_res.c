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
struct ocfs2_lock_res {int l_flags; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int OCFS2_LOCK_NEEDS_REFRESH ; 
 int OCFS2_LOCK_REFRESHING ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_wait_on_refreshing_lock (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ocfs2_should_refresh_lock_res(struct ocfs2_lock_res *lockres)
{
	unsigned long flags;
	int status = 0;

	mlog_entry_void();

refresh_check:
	spin_lock_irqsave(&lockres->l_lock, flags);
	if (!(lockres->l_flags & OCFS2_LOCK_NEEDS_REFRESH)) {
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		goto bail;
	}

	if (lockres->l_flags & OCFS2_LOCK_REFRESHING) {
		spin_unlock_irqrestore(&lockres->l_lock, flags);

		ocfs2_wait_on_refreshing_lock(lockres);
		goto refresh_check;
	}

	/* Ok, I'll be the one to refresh this lock. */
	lockres_or_flags(lockres, OCFS2_LOCK_REFRESHING);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	status = 1;
bail:
	mlog_exit(status);
	return status;
}