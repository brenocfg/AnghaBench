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
 int DQUOT_SPACE_RESERVE ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int MAXQUOTAS ; 
 int QUOTA_OK ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  dquot_decr_space (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_free_reserved_space (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_warnings (scalar_t__*,char*) ; 
 char info_bdq_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_decr_space (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_dquot_dirty (scalar_t__) ; 
 TYPE_1__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int __dquot_free_space(struct inode *inode, qsize_t number, int flags)
{
	unsigned int cnt;
	char warntype[MAXQUOTAS];
	int reserve = flags & DQUOT_SPACE_RESERVE;

	/* First test before acquiring mutex - solves deadlocks when we
         * re-enter the quota code and are already holding the mutex */
	if (IS_NOQUOTA(inode)) {
out_sub:
		inode_decr_space(inode, number, reserve);
		return QUOTA_OK;
	}

	down_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
	/* Now recheck reliably when holding dqptr_sem */
	if (IS_NOQUOTA(inode)) {
		up_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
		goto out_sub;
	}
	spin_lock(&dq_data_lock);
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!inode->i_dquot[cnt])
			continue;
		warntype[cnt] = info_bdq_free(inode->i_dquot[cnt], number);
		if (reserve)
			dquot_free_reserved_space(inode->i_dquot[cnt], number);
		else
			dquot_decr_space(inode->i_dquot[cnt], number);
	}
	inode_decr_space(inode, number, reserve);
	spin_unlock(&dq_data_lock);

	if (reserve)
		goto out_unlock;
	/* Dirtify all the dquots - this can block when journalling */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++)
		if (inode->i_dquot[cnt])
			mark_dquot_dirty(inode->i_dquot[cnt]);
out_unlock:
	flush_warnings(inode->i_dquot, warntype);
	up_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
	return QUOTA_OK;
}