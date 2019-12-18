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
struct user_lock_res {int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_name; int /*<<< orphan*/  l_namelen; } ;

/* Variables and functions */
 int LKM_EXMODE ; 
 int LKM_PRMODE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  __user_dlm_cond_queue_lockres (struct user_lock_res*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_dlm_dec_holders (struct user_lock_res*,int) ; 

void user_dlm_cluster_unlock(struct user_lock_res *lockres,
			     int level)
{
	if (level != LKM_EXMODE &&
	    level != LKM_PRMODE) {
		mlog(ML_ERROR, "lockres %.*s: invalid request!\n",
		     lockres->l_namelen, lockres->l_name);
		return;
	}

	spin_lock(&lockres->l_lock);
	user_dlm_dec_holders(lockres, level);
	__user_dlm_cond_queue_lockres(lockres);
	spin_unlock(&lockres->l_lock);
}