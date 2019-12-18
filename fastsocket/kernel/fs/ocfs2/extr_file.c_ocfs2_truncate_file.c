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
typedef  scalar_t__ u64 ;
struct ocfs2_truncate_context {int dummy; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_blkno; int /*<<< orphan*/  i_flags; } ;
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int ip_dyn_features; scalar_t__ ip_clusters; int /*<<< orphan*/  ip_alloc_sem; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,...) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,unsigned long long,scalar_t__,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_commit_truncate (struct ocfs2_super*,struct inode*,struct buffer_head*,struct ocfs2_truncate_context*) ; 
 int ocfs2_orphan_for_truncate (struct ocfs2_super*,struct inode*,struct buffer_head*,scalar_t__) ; 
 int ocfs2_prepare_truncate (struct ocfs2_super*,struct inode*,struct buffer_head*,struct ocfs2_truncate_context**) ; 
 int ocfs2_truncate_inline (struct inode*,struct buffer_head*,scalar_t__,scalar_t__,int) ; 
 int ocfs2_try_remove_refcount_tree (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  unmap_mapping_range (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_truncate_file(struct inode *inode,
			       struct buffer_head *di_bh,
			       u64 new_i_size)
{
	int status = 0;
	struct ocfs2_dinode *fe = NULL;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_truncate_context *tc = NULL;

	mlog_entry("(inode = %llu, new_i_size = %llu\n",
		   (unsigned long long)OCFS2_I(inode)->ip_blkno,
		   (unsigned long long)new_i_size);

	/* We trust di_bh because it comes from ocfs2_inode_lock(), which
	 * already validated it */
	fe = (struct ocfs2_dinode *) di_bh->b_data;

	mlog_bug_on_msg(le64_to_cpu(fe->i_size) != i_size_read(inode),
			"Inode %llu, inode i_size = %lld != di "
			"i_size = %llu, i_flags = 0x%x\n",
			(unsigned long long)OCFS2_I(inode)->ip_blkno,
			i_size_read(inode),
			(unsigned long long)le64_to_cpu(fe->i_size),
			le32_to_cpu(fe->i_flags));

	if (new_i_size > le64_to_cpu(fe->i_size)) {
		mlog(0, "asked to truncate file with size (%llu) to size (%llu)!\n",
		     (unsigned long long)le64_to_cpu(fe->i_size),
		     (unsigned long long)new_i_size);
		status = -EINVAL;
		mlog_errno(status);
		goto bail;
	}

	mlog(0, "inode %llu, i_size = %llu, new_i_size = %llu\n",
	     (unsigned long long)le64_to_cpu(fe->i_blkno),
	     (unsigned long long)le64_to_cpu(fe->i_size),
	     (unsigned long long)new_i_size);

	/* lets handle the simple truncate cases before doing any more
	 * cluster locking. */
	if (new_i_size == le64_to_cpu(fe->i_size))
		goto bail;

	down_write(&OCFS2_I(inode)->ip_alloc_sem);

	/*
	 * The inode lock forced other nodes to sync and drop their
	 * pages, which (correctly) happens even if we have a truncate
	 * without allocation change - ocfs2 cluster sizes can be much
	 * greater than page size, so we have to truncate them
	 * anyway.
	 */
	unmap_mapping_range(inode->i_mapping, new_i_size + PAGE_SIZE - 1, 0, 1);
	truncate_inode_pages(inode->i_mapping, new_i_size);

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		status = ocfs2_truncate_inline(inode, di_bh, new_i_size,
					       i_size_read(inode), 1);
		if (status)
			mlog_errno(status);

		goto bail_unlock_sem;
	}

	/* alright, we're going to need to do a full blown alloc size
	 * change. Orphan the inode so that recovery can complete the
	 * truncate if necessary. This does the task of marking
	 * i_size. */
	status = ocfs2_orphan_for_truncate(osb, inode, di_bh, new_i_size);
	if (status < 0) {
		mlog_errno(status);
		goto bail_unlock_sem;
	}

	status = ocfs2_prepare_truncate(osb, inode, di_bh, &tc);
	if (status < 0) {
		mlog_errno(status);
		goto bail_unlock_sem;
	}

	status = ocfs2_commit_truncate(osb, inode, di_bh, tc);
	if (status < 0) {
		mlog_errno(status);
		goto bail_unlock_sem;
	}

	/* TODO: orphan dir cleanup here. */
bail_unlock_sem:
	up_write(&OCFS2_I(inode)->ip_alloc_sem);

bail:
	if (!status && OCFS2_I(inode)->ip_clusters == 0)
		status = ocfs2_try_remove_refcount_tree(inode, di_bh);

	mlog_exit(status);
	return status;
}