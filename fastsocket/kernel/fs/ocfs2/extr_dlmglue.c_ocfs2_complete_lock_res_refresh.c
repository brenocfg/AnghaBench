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
struct ocfs2_lock_res {int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_LOCK_NEEDS_REFRESH ; 
 int /*<<< orphan*/  OCFS2_LOCK_REFRESHING ; 
 int /*<<< orphan*/  lockres_clear_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit_void () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ocfs2_complete_lock_res_refresh(struct ocfs2_lock_res *lockres,
						   int status)
{
	unsigned long flags;
	mlog_entry_void();

	spin_lock_irqsave(&lockres->l_lock, flags);
	lockres_clear_flags(lockres, OCFS2_LOCK_REFRESHING);
	if (!status)
		lockres_clear_flags(lockres, OCFS2_LOCK_NEEDS_REFRESH);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	wake_up(&lockres->l_event);

	mlog_exit_void();
}