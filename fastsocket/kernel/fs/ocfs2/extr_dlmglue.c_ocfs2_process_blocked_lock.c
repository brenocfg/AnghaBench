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
struct ocfs2_unblock_ctl {scalar_t__ unblock_action; scalar_t__ requeue; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int l_flags; TYPE_1__* l_ops; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* post_unlock ) (struct ocfs2_super*,struct ocfs2_lock_res*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCFS2_LOCK_FREEING ; 
 int /*<<< orphan*/  OCFS2_LOCK_QUEUED ; 
 scalar_t__ UNBLOCK_CONTINUE ; 
 int /*<<< orphan*/  lockres_clear_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  ocfs2_schedule_blocked_lock (struct ocfs2_super*,struct ocfs2_lock_res*) ; 
 int ocfs2_unblock_lock (struct ocfs2_super*,struct ocfs2_lock_res*,struct ocfs2_unblock_ctl*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ocfs2_super*,struct ocfs2_lock_res*) ; 

__attribute__((used)) static void ocfs2_process_blocked_lock(struct ocfs2_super *osb,
				       struct ocfs2_lock_res *lockres)
{
	int status;
	struct ocfs2_unblock_ctl ctl = {0, 0,};
	unsigned long flags;

	/* Our reference to the lockres in this function can be
	 * considered valid until we remove the OCFS2_LOCK_QUEUED
	 * flag. */

	mlog_entry_void();

	BUG_ON(!lockres);
	BUG_ON(!lockres->l_ops);

	mlog(0, "lockres %s blocked.\n", lockres->l_name);

	/* Detect whether a lock has been marked as going away while
	 * the downconvert thread was processing other things. A lock can
	 * still be marked with OCFS2_LOCK_FREEING after this check,
	 * but short circuiting here will still save us some
	 * performance. */
	spin_lock_irqsave(&lockres->l_lock, flags);
	if (lockres->l_flags & OCFS2_LOCK_FREEING)
		goto unqueue;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	status = ocfs2_unblock_lock(osb, lockres, &ctl);
	if (status < 0)
		mlog_errno(status);

	spin_lock_irqsave(&lockres->l_lock, flags);
unqueue:
	if (lockres->l_flags & OCFS2_LOCK_FREEING || !ctl.requeue) {
		lockres_clear_flags(lockres, OCFS2_LOCK_QUEUED);
	} else
		ocfs2_schedule_blocked_lock(osb, lockres);

	mlog(0, "lockres %s, requeue = %s.\n", lockres->l_name,
	     ctl.requeue ? "yes" : "no");
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	if (ctl.unblock_action != UNBLOCK_CONTINUE
	    && lockres->l_ops->post_unlock)
		lockres->l_ops->post_unlock(osb, lockres);

	mlog_exit_void();
}