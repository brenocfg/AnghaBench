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
struct inode {scalar_t__ i_uid; scalar_t__ i_gid; int /*<<< orphan*/  i_sb; struct dquot** i_dquot; } ;
struct iattr {int ia_valid; scalar_t__ ia_uid; scalar_t__ ia_gid; } ;
struct dquot {int dummy; } ;
typedef  scalar_t__ qsize_t ;
struct TYPE_2__ {int /*<<< orphan*/  dqptr_sem; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_UID ; 
 size_t GRPQUOTA ; 
 scalar_t__ IS_NOQUOTA (struct inode*) ; 
 int MAXQUOTAS ; 
 int NO_QUOTA ; 
 char QUOTA_NL_NOWARN ; 
 int QUOTA_OK ; 
 size_t USRQUOTA ; 
 int check_bdq (struct dquot*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int check_idq (struct dquot*,int,char*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 struct dquot* dqget (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  dqput (struct dquot*) ; 
 int /*<<< orphan*/  dquot_decr_inodes (struct dquot*,int) ; 
 int /*<<< orphan*/  dquot_decr_space (struct dquot*,scalar_t__) ; 
 int /*<<< orphan*/  dquot_free_reserved_space (struct dquot*,scalar_t__) ; 
 int /*<<< orphan*/  dquot_incr_inodes (struct dquot*,int) ; 
 int /*<<< orphan*/  dquot_incr_space (struct dquot*,scalar_t__) ; 
 int /*<<< orphan*/  dquot_resv_space (struct dquot*,scalar_t__) ; 
 int /*<<< orphan*/  flush_warnings (struct dquot**,char*) ; 
 char info_bdq_free (struct dquot*,scalar_t__) ; 
 char info_idq_free (struct dquot*,int) ; 
 scalar_t__ inode_get_bytes (struct inode*) ; 
 scalar_t__ inode_get_rsv_space (struct inode*) ; 
 int /*<<< orphan*/  mark_dquot_dirty (struct dquot*) ; 
 TYPE_1__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dquot_transfer(struct inode *inode, struct iattr *iattr)
{
	qsize_t space, cur_space;
	qsize_t rsv_space = 0;
	struct dquot *transfer_from[MAXQUOTAS];
	struct dquot *transfer_to[MAXQUOTAS];
	int cnt, ret = QUOTA_OK;
	int chuid = iattr->ia_valid & ATTR_UID && inode->i_uid != iattr->ia_uid,
	    chgid = iattr->ia_valid & ATTR_GID && inode->i_gid != iattr->ia_gid;
	char warntype_to[MAXQUOTAS];
	char warntype_from_inodes[MAXQUOTAS], warntype_from_space[MAXQUOTAS];

	/* First test before acquiring mutex - solves deadlocks when we
         * re-enter the quota code and are already holding the mutex */
	if (IS_NOQUOTA(inode))
		return QUOTA_OK;
	/* Initialize the arrays */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		transfer_from[cnt] = NULL;
		transfer_to[cnt] = NULL;
		warntype_to[cnt] = QUOTA_NL_NOWARN;
	}
	if (chuid)
		transfer_to[USRQUOTA] = dqget(inode->i_sb, iattr->ia_uid,
					      USRQUOTA);
	if (chgid)
		transfer_to[GRPQUOTA] = dqget(inode->i_sb, iattr->ia_gid,
					      GRPQUOTA);

	down_write(&sb_dqopt(inode->i_sb)->dqptr_sem);
	/* Now recheck reliably when holding dqptr_sem */
	if (IS_NOQUOTA(inode)) {	/* File without quota accounting? */
		up_write(&sb_dqopt(inode->i_sb)->dqptr_sem);
		goto put_all;
	}
	spin_lock(&dq_data_lock);
	cur_space = inode_get_bytes(inode);
	rsv_space = inode_get_rsv_space(inode);
	space = cur_space + rsv_space;
	/* Build the transfer_from list and check the limits */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (!transfer_to[cnt])
			continue;
		transfer_from[cnt] = inode->i_dquot[cnt];
		if (check_idq(transfer_to[cnt], 1, warntype_to + cnt) ==
		    NO_QUOTA || check_bdq(transfer_to[cnt], space, 0,
		    warntype_to + cnt) == NO_QUOTA)
			goto over_quota;
	}

	/*
	 * Finally perform the needed transfer from transfer_from to transfer_to
	 */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		/*
		 * Skip changes for same uid or gid or for turned off quota-type.
		 */
		if (!transfer_to[cnt])
			continue;

		/* Due to IO error we might not have transfer_from[] structure */
		if (transfer_from[cnt]) {
			warntype_from_inodes[cnt] =
				info_idq_free(transfer_from[cnt], 1);
			warntype_from_space[cnt] =
				info_bdq_free(transfer_from[cnt], space);
			dquot_decr_inodes(transfer_from[cnt], 1);
			dquot_decr_space(transfer_from[cnt], cur_space);
			dquot_free_reserved_space(transfer_from[cnt],
						  rsv_space);
		}

		dquot_incr_inodes(transfer_to[cnt], 1);
		dquot_incr_space(transfer_to[cnt], cur_space);
		dquot_resv_space(transfer_to[cnt], rsv_space);

		inode->i_dquot[cnt] = transfer_to[cnt];
	}
	spin_unlock(&dq_data_lock);
	up_write(&sb_dqopt(inode->i_sb)->dqptr_sem);

	/* Dirtify all the dquots - this can block when journalling */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		if (transfer_from[cnt])
			mark_dquot_dirty(transfer_from[cnt]);
		if (transfer_to[cnt]) {
			mark_dquot_dirty(transfer_to[cnt]);
			/* The reference we got is transferred to the inode */
			transfer_to[cnt] = NULL;
		}
	}
warn_put_all:
	flush_warnings(transfer_to, warntype_to);
	flush_warnings(transfer_from, warntype_from_inodes);
	flush_warnings(transfer_from, warntype_from_space);
put_all:
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		dqput(transfer_from[cnt]);
		dqput(transfer_to[cnt]);
	}
	return ret;
over_quota:
	spin_unlock(&dq_data_lock);
	up_write(&sb_dqopt(inode->i_sb)->dqptr_sem);
	/* Clear dquot pointers we don't want to dqput() */
	for (cnt = 0; cnt < MAXQUOTAS; cnt++)
		transfer_from[cnt] = NULL;
	ret = NO_QUOTA;
	goto warn_put_all;
}