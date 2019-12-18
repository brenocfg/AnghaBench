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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_QUOTA_BLOCK_UPDATE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_SB (struct super_block*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_commit_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_journal_access_dq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_modify_bh(struct inode *inode, struct buffer_head *bh,
		void (*modify)(struct buffer_head *, void *), void *private)
{
	struct super_block *sb = inode->i_sb;
	handle_t *handle;
	int status;

	handle = ocfs2_start_trans(OCFS2_SB(sb),
				   OCFS2_QUOTA_BLOCK_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		return status;
	}
	status = ocfs2_journal_access_dq(handle, INODE_CACHE(inode), bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		ocfs2_commit_trans(OCFS2_SB(sb), handle);
		return status;
	}
	lock_buffer(bh);
	modify(bh, private);
	unlock_buffer(bh);
	status = ocfs2_journal_dirty(handle, bh);
	if (status < 0) {
		mlog_errno(status);
		ocfs2_commit_trans(OCFS2_SB(sb), handle);
		return status;
	}
	status = ocfs2_commit_trans(OCFS2_SB(sb), handle);
	if (status < 0) {
		mlog_errno(status);
		return status;
	}
	return 0;
}