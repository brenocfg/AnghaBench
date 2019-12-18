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
struct ocfs2_super {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_open_lockres; int /*<<< orphan*/  ip_inode_lockres; int /*<<< orphan*/  ip_rw_lockres; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_create_new_lock (struct ocfs2_super*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ocfs2_inode_is_new (struct inode*) ; 

int ocfs2_create_new_inode_locks(struct inode *inode)
{
	int ret;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	BUG_ON(!inode);
	BUG_ON(!ocfs2_inode_is_new(inode));

	mlog_entry_void();

	mlog(0, "Inode %llu\n", (unsigned long long)OCFS2_I(inode)->ip_blkno);

	/* NOTE: That we don't increment any of the holder counts, nor
	 * do we add anything to a journal handle. Since this is
	 * supposed to be a new inode which the cluster doesn't know
	 * about yet, there is no need to.  As far as the LVB handling
	 * is concerned, this is basically like acquiring an EX lock
	 * on a resource which has an invalid one -- we'll set it
	 * valid when we release the EX. */

	ret = ocfs2_create_new_lock(osb, &OCFS2_I(inode)->ip_rw_lockres, 1, 1);
	if (ret) {
		mlog_errno(ret);
		goto bail;
	}

	/*
	 * We don't want to use DLM_LKF_LOCAL on a meta data lock as they
	 * don't use a generation in their lock names.
	 */
	ret = ocfs2_create_new_lock(osb, &OCFS2_I(inode)->ip_inode_lockres, 1, 0);
	if (ret) {
		mlog_errno(ret);
		goto bail;
	}

	ret = ocfs2_create_new_lock(osb, &OCFS2_I(inode)->ip_open_lockres, 0, 0);
	if (ret) {
		mlog_errno(ret);
		goto bail;
	}

bail:
	mlog_exit(ret);
	return ret;
}