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
struct inode {int /*<<< orphan*/  i_sb; scalar_t__* i_dquot; } ;
typedef  int /*<<< orphan*/  qsize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dqptr_sem; } ;

/* Variables and functions */
 int DQUOT_SPACE_NOFAIL ; 
 int DQUOT_SPACE_RESERVE ; 
 int DQUOT_SPACE_WARN ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int MAXQUOTAS ; 
 int NO_QUOTA ; 
 char QUOTA_NL_NOWARN ; 
 int QUOTA_OK ; 
 int check_bdq (scalar_t__,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  dquot_incr_space (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_resv_space (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_warnings (scalar_t__*,char*) ; 
 int /*<<< orphan*/  inode_incr_space (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_dquot_dirty (scalar_t__) ; 
 TYPE_1__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int __dquot_alloc_space(struct inode *inode, qsize_t number, int flags)
{
	int cnt, ret = QUOTA_OK;
	char warntype[MAXQUOTAS];
	int warn = flags & DQUOT_SPACE_WARN;
	int reserve = flags & DQUOT_SPACE_RESERVE;
	int nofail = flags & DQUOT_SPACE_NOFAIL;

	/*
	 * First test before acquiring mutex - solves deadlocks when we
	 * re-enter the quota code and are already holding the mutex
	 */
	if (IS_NOQUOTA(inode)) {
		inode_incr_space(inode, number, reserve);
		goto out;
	}

	down_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
	if (IS_NOQUOTA(inode)) {
		inode_incr_space(inode, number, reserve);
		goto out_unlock;
	}

	for (cnt = 0; cnt < MAXQUOTAS; cnt++)
		warntype[cnt] = QUOTA_NL_NOWARN;

	spin_lock(&dq_data_lock);
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!inode->i_dquot[cnt])
			continue;
		if (check_bdq(inode->i_dquot[cnt], number, warn, warntype+cnt)
		    == NO_QUOTA && !nofail) {
			ret = NO_QUOTA;
			spin_unlock(&dq_data_lock);
			goto out_flush_warn;
		}
	}
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!inode->i_dquot[cnt])
			continue;
		if (reserve)
			dquot_resv_space(inode->i_dquot[cnt], number);
		else
			dquot_incr_space(inode->i_dquot[cnt], number);
	}
	inode_incr_space(inode, number, reserve);
	spin_unlock(&dq_data_lock);

	if (reserve)
		goto out_flush_warn;
	/* Dirtify all the dquots - this can block when journalling */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++)
		if (inode->i_dquot[cnt])
			mark_dquot_dirty(inode->i_dquot[cnt]);
out_flush_warn:
	flush_warnings(inode->i_dquot, warntype);
out_unlock:
	up_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
out:
	return ret;
}