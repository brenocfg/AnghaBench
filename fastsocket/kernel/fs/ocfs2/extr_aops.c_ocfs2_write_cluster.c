#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_write_ctxt {int w_num_pages; int /*<<< orphan*/ * w_pages; int /*<<< orphan*/  w_dealloc; int /*<<< orphan*/  w_handle; int /*<<< orphan*/  w_di_bh; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {scalar_t__ ip_blkno; } ;
struct TYPE_5__ {scalar_t__ s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_4__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_add_inode_data (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*,int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_clusters_to_blocks (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_error (TYPE_1__*,char*,unsigned long long,unsigned long long) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_mark_extent_written (struct inode*,struct ocfs2_extent_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,int /*<<< orphan*/ *) ; 
 int ocfs2_prepare_page_for_write (struct inode*,scalar_t__*,struct ocfs2_write_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_write_failure (struct inode*,struct ocfs2_write_ctxt*,scalar_t__,unsigned int) ; 

__attribute__((used)) static int ocfs2_write_cluster(struct address_space *mapping,
			       u32 phys, unsigned int unwritten,
			       unsigned int should_zero,
			       struct ocfs2_alloc_context *data_ac,
			       struct ocfs2_alloc_context *meta_ac,
			       struct ocfs2_write_ctxt *wc, u32 cpos,
			       loff_t user_pos, unsigned user_len)
{
	int ret, i, new;
	u64 v_blkno, p_blkno;
	struct inode *inode = mapping->host;
	struct ocfs2_extent_tree et;

	new = phys == 0 ? 1 : 0;
	if (new) {
		u32 tmp_pos;

		/*
		 * This is safe to call with the page locks - it won't take
		 * any additional semaphores or cluster locks.
		 */
		tmp_pos = cpos;
		ret = ocfs2_add_inode_data(OCFS2_SB(inode->i_sb), inode,
					   &tmp_pos, 1, 0, wc->w_di_bh,
					   wc->w_handle, data_ac,
					   meta_ac, NULL);
		/*
		 * This shouldn't happen because we must have already
		 * calculated the correct meta data allocation required. The
		 * internal tree allocation code should know how to increase
		 * transaction credits itself.
		 *
		 * If need be, we could handle -EAGAIN for a
		 * RESTART_TRANS here.
		 */
		mlog_bug_on_msg(ret == -EAGAIN,
				"Inode %llu: EAGAIN return during allocation.\n",
				(unsigned long long)OCFS2_I(inode)->ip_blkno);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}
	} else if (unwritten) {
		ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode),
					      wc->w_di_bh);
		ret = ocfs2_mark_extent_written(inode, &et,
						wc->w_handle, cpos, 1, phys,
						meta_ac, &wc->w_dealloc);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}
	}

	if (should_zero)
		v_blkno = ocfs2_clusters_to_blocks(inode->i_sb, cpos);
	else
		v_blkno = user_pos >> inode->i_sb->s_blocksize_bits;

	/*
	 * The only reason this should fail is due to an inability to
	 * find the extent added.
	 */
	ret = ocfs2_extent_map_get_blocks(inode, v_blkno, &p_blkno, NULL,
					  NULL);
	if (ret < 0) {
		ocfs2_error(inode->i_sb, "Corrupting extend for inode %llu, "
			    "at logical block %llu",
			    (unsigned long long)OCFS2_I(inode)->ip_blkno,
			    (unsigned long long)v_blkno);
		goto out;
	}

	BUG_ON(p_blkno == 0);

	for(i = 0; i < wc->w_num_pages; i++) {
		int tmpret;

		tmpret = ocfs2_prepare_page_for_write(inode, &p_blkno, wc,
						      wc->w_pages[i], cpos,
						      user_pos, user_len,
						      should_zero);
		if (tmpret) {
			mlog_errno(tmpret);
			if (ret == 0)
				ret = tmpret;
		}
	}

	/*
	 * We only have cleanup to do in case of allocating write.
	 */
	if (ret && new)
		ocfs2_write_failure(inode, wc, user_pos, user_len);

out:

	return ret;
}