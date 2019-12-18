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
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int MAXQUOTAS ; 
 int QUOTA_OK ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  dquot_claim_reserved_space (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_claim_rsv_space (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_dquot_dirty (scalar_t__) ; 
 TYPE_1__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int dquot_claim_space(struct inode *inode, qsize_t number)
{
	int cnt;
	int ret = QUOTA_OK;

	if (IS_NOQUOTA(inode)) {
		inode_claim_rsv_space(inode, number);
		goto out;
	}

	down_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
	if (IS_NOQUOTA(inode))	{
		up_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
		inode_claim_rsv_space(inode, number);
		goto out;
	}

	spin_lock(&dq_data_lock);
	/* Claim reserved quotas to allocated quotas */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (inode->i_dquot[cnt])
			dquot_claim_reserved_space(inode->i_dquot[cnt],
							number);
	}
	/* Update inode bytes */
	inode_claim_rsv_space(inode, number);
	spin_unlock(&dq_data_lock);
	/* Dirtify all the dquots - this can block when journalling */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++)
		if (inode->i_dquot[cnt])
			mark_dquot_dirty(inode->i_dquot[cnt]);
	up_read(&sb_dqopt(inode->i_sb)->dqptr_sem);
out:
	return ret;
}