#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u16 ;
struct ocfs2_group_desc {void* bg_next_group; void* bg_blkno; } ;
struct TYPE_5__ {TYPE_1__* cl_recs; } ;
struct TYPE_6__ {TYPE_2__ i_chain; } ;
struct ocfs2_dinode {TYPE_3__ id2; void* i_blkno; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {void* c_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_GROUP_DESC (struct ocfs2_group_desc*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 void* cpu_to_le64 (scalar_t__) ; 
 scalar_t__ le64_to_cpu (void*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,size_t,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_gd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_relink_block_group(handle_t *handle,
				    struct inode *alloc_inode,
				    struct buffer_head *fe_bh,
				    struct buffer_head *bg_bh,
				    struct buffer_head *prev_bg_bh,
				    u16 chain)
{
	int status;
	/* there is a really tiny chance the journal calls could fail,
	 * but we wouldn't want inconsistent blocks in *any* case. */
	u64 fe_ptr, bg_ptr, prev_bg_ptr;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) fe_bh->b_data;
	struct ocfs2_group_desc *bg = (struct ocfs2_group_desc *) bg_bh->b_data;
	struct ocfs2_group_desc *prev_bg = (struct ocfs2_group_desc *) prev_bg_bh->b_data;

	/* The caller got these descriptors from
	 * ocfs2_read_group_descriptor().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(bg));
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(prev_bg));

	mlog(0, "Suballoc %llu, chain %u, move group %llu to top, prev = %llu\n",
	     (unsigned long long)le64_to_cpu(fe->i_blkno), chain,
	     (unsigned long long)le64_to_cpu(bg->bg_blkno),
	     (unsigned long long)le64_to_cpu(prev_bg->bg_blkno));

	fe_ptr = le64_to_cpu(fe->id2.i_chain.cl_recs[chain].c_blkno);
	bg_ptr = le64_to_cpu(bg->bg_next_group);
	prev_bg_ptr = le64_to_cpu(prev_bg->bg_next_group);

	status = ocfs2_journal_access_gd(handle, INODE_CACHE(alloc_inode),
					 prev_bg_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto out_rollback;
	}

	prev_bg->bg_next_group = bg->bg_next_group;

	status = ocfs2_journal_dirty(handle, prev_bg_bh);
	if (status < 0) {
		mlog_errno(status);
		goto out_rollback;
	}

	status = ocfs2_journal_access_gd(handle, INODE_CACHE(alloc_inode),
					 bg_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto out_rollback;
	}

	bg->bg_next_group = fe->id2.i_chain.cl_recs[chain].c_blkno;

	status = ocfs2_journal_dirty(handle, bg_bh);
	if (status < 0) {
		mlog_errno(status);
		goto out_rollback;
	}

	status = ocfs2_journal_access_di(handle, INODE_CACHE(alloc_inode),
					 fe_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto out_rollback;
	}

	fe->id2.i_chain.cl_recs[chain].c_blkno = bg->bg_blkno;

	status = ocfs2_journal_dirty(handle, fe_bh);
	if (status < 0) {
		mlog_errno(status);
		goto out_rollback;
	}

	status = 0;
out_rollback:
	if (status < 0) {
		fe->id2.i_chain.cl_recs[chain].c_blkno = cpu_to_le64(fe_ptr);
		bg->bg_next_group = cpu_to_le64(bg_ptr);
		prev_bg->bg_next_group = cpu_to_le64(prev_bg_ptr);
	}

	mlog_exit(status);
	return status;
}