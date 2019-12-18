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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ocfs2_super {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INODE_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocfs2_get_suballoc_slot_bit (struct ocfs2_super*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_test_suballoc_bit (struct ocfs2_super*,struct inode*,struct buffer_head*,scalar_t__,scalar_t__,int*) ; 

int ocfs2_test_inode_bit(struct ocfs2_super *osb, u64 blkno, int *res)
{
	int status;
	u16 suballoc_bit = 0, suballoc_slot = 0;
	struct inode *inode_alloc_inode;
	struct buffer_head *alloc_bh = NULL;

	mlog_entry("blkno: %llu", (unsigned long long)blkno);

	status = ocfs2_get_suballoc_slot_bit(osb, blkno, &suballoc_slot,
					     &suballoc_bit);
	if (status < 0) {
		mlog(ML_ERROR, "get alloc slot and bit failed %d\n", status);
		goto bail;
	}

	inode_alloc_inode =
		ocfs2_get_system_file_inode(osb, INODE_ALLOC_SYSTEM_INODE,
					    suballoc_slot);
	if (!inode_alloc_inode) {
		/* the error code could be inaccurate, but we are not able to
		 * get the correct one. */
		status = -EINVAL;
		mlog(ML_ERROR, "unable to get alloc inode in slot %u\n",
		     (u32)suballoc_slot);
		goto bail;
	}

	mutex_lock(&inode_alloc_inode->i_mutex);
	status = ocfs2_inode_lock(inode_alloc_inode, &alloc_bh, 0);
	if (status < 0) {
		mutex_unlock(&inode_alloc_inode->i_mutex);
		mlog(ML_ERROR, "lock on alloc inode on slot %u failed %d\n",
		     (u32)suballoc_slot, status);
		goto bail;
	}

	status = ocfs2_test_suballoc_bit(osb, inode_alloc_inode, alloc_bh,
					 blkno, suballoc_bit, res);
	if (status < 0)
		mlog(ML_ERROR, "test suballoc bit failed %d\n", status);

	ocfs2_inode_unlock(inode_alloc_inode, 0);
	mutex_unlock(&inode_alloc_inode->i_mutex);

	iput(inode_alloc_inode);
	brelse(alloc_bh);
bail:
	mlog_exit(status);
	return status;
}