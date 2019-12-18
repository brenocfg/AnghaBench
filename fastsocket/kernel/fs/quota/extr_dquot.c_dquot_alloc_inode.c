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
 scalar_t__ IS_NOQUOTA (struct inode const*) ; 
 int MAXQUOTAS ; 
 int NO_QUOTA ; 
 char QUOTA_NL_NOWARN ; 
 int QUOTA_OK ; 
 int check_idq (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  dquot_incr_inodes (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_warnings (scalar_t__*,char*) ; 
 int /*<<< orphan*/  mark_dquot_dirty (scalar_t__) ; 
 TYPE_1__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dquot_alloc_inode(const struct inode *inode, qsize_t number)
{
	int cnt, ret = NO_QUOTA;
	char warntype[MAXQUOTAS];

	/* First test before acquiring mutex - solves deadlocks when we
         * re-enter the quota code and are already holding the mutex */
	if (IS_NOQUOTA(inode))
		return QUOTA_OK;
	for (cnt = 0; cnt < MAXQUOTAS; cnt++)
		warntype[cnt] = QUOTA_NL_NOWARN;
	down_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
	if (IS_NOQUOTA(inode)) {
		up_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
		return QUOTA_OK;
	}
	spin_lock(&dq_data_lock);
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!inode->i_dquot[cnt])
			continue;
		if (check_idq(inode->i_dquot[cnt], number, warntype+cnt)
		    == NO_QUOTA)
			goto warn_put_all;
	}

	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!inode->i_dquot[cnt])
			continue;
		dquot_incr_inodes(inode->i_dquot[cnt], number);
	}
	ret = QUOTA_OK;
warn_put_all:
	spin_unlock(&dq_data_lock);
	if (ret == QUOTA_OK)
		/* Dirtify all the dquots - this can block when journalling */
		for (cnt = 0; cnt < MAXQUOTAS; cnt++)
			if (inode->i_dquot[cnt])
				mark_dquot_dirty(inode->i_dquot[cnt]);
	flush_warnings(inode->i_dquot, warntype);
	up_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
	return ret;
}