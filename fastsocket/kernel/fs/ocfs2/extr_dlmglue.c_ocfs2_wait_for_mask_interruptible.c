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
struct ocfs2_mask_waiter {int mw_status; int /*<<< orphan*/  mw_complete; } ;
struct ocfs2_lock_res {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMPLETION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockres_remove_mask_waiter (struct ocfs2_lock_res*,struct ocfs2_mask_waiter*) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_wait_for_mask_interruptible(struct ocfs2_mask_waiter *mw,
					     struct ocfs2_lock_res *lockres)
{
	int ret;

	ret = wait_for_completion_interruptible(&mw->mw_complete);
	if (ret)
		lockres_remove_mask_waiter(lockres, mw);
	else
		ret = mw->mw_status;
	/* Re-arm the completion in case we want to wait on it again */
	INIT_COMPLETION(mw->mw_complete);
	return ret;
}