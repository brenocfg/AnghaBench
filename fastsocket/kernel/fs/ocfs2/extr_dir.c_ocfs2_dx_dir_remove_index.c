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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_suballoc_bit; int /*<<< orphan*/  dr_blkno; int /*<<< orphan*/  dr_suballoc_slot; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_dx_root; int /*<<< orphan*/  i_dyn_features; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  ip_dyn_features; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXTENT_ALLOC_SYSTEM_INODE ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_DX_ROOT_REMOVE_CREDITS ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INDEXED_DIR_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (unsigned long long) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_free_suballoc_bits (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_which_suballoc_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_dx_dir_remove_index(struct inode *dir,
				     struct buffer_head *di_bh,
				     struct buffer_head *dx_root_bh)
{
	int ret;
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct ocfs2_dx_root_block *dx_root;
	struct inode *dx_alloc_inode = NULL;
	struct buffer_head *dx_alloc_bh = NULL;
	handle_t *handle;
	u64 blk;
	u16 bit;
	u64 bg_blkno;

	dx_root = (struct ocfs2_dx_root_block *) dx_root_bh->b_data;

	dx_alloc_inode = ocfs2_get_system_file_inode(osb,
					EXTENT_ALLOC_SYSTEM_INODE,
					le16_to_cpu(dx_root->dr_suballoc_slot));
	if (!dx_alloc_inode) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}
	mutex_lock(&dx_alloc_inode->i_mutex);

	ret = ocfs2_inode_lock(dx_alloc_inode, &dx_alloc_bh, 1);
	if (ret) {
		mlog_errno(ret);
		goto out_mutex;
	}

	handle = ocfs2_start_trans(osb, OCFS2_DX_ROOT_REMOVE_CREDITS);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out_unlock;
	}

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(dir), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	OCFS2_I(dir)->ip_dyn_features &= ~OCFS2_INDEXED_DIR_FL;
	di->i_dyn_features = cpu_to_le16(OCFS2_I(dir)->ip_dyn_features);
	di->i_dx_root = cpu_to_le64(0ULL);

	ocfs2_journal_dirty(handle, di_bh);

	blk = le64_to_cpu(dx_root->dr_blkno);
	bit = le16_to_cpu(dx_root->dr_suballoc_bit);
	bg_blkno = ocfs2_which_suballoc_group(blk, bit);
	ret = ocfs2_free_suballoc_bits(handle, dx_alloc_inode, dx_alloc_bh,
				       bit, bg_blkno, 1);
	if (ret)
		mlog_errno(ret);

out_commit:
	ocfs2_commit_trans(osb, handle);

out_unlock:
	ocfs2_inode_unlock(dx_alloc_inode, 1);

out_mutex:
	mutex_unlock(&dx_alloc_inode->i_mutex);
	brelse(dx_alloc_bh);
out:
	iput(dx_alloc_inode);
	return ret;
}