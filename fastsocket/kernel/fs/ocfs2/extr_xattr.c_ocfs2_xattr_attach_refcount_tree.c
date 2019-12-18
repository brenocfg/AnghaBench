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
struct ocfs2_inode_info {int ip_dyn_features; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_xattr_loc; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_XATTR_FL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_read_xattr_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int ocfs2_xattr_block_attach_refcount (struct inode*,struct buffer_head*,struct ocfs2_caching_info*,struct buffer_head*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int ocfs2_xattr_inline_attach_refcount (struct inode*,struct buffer_head*,struct ocfs2_caching_info*,struct buffer_head*,struct ocfs2_cached_dealloc_ctxt*) ; 

int ocfs2_xattr_attach_refcount_tree(struct inode *inode,
				     struct buffer_head *fe_bh,
				     struct ocfs2_caching_info *ref_ci,
				     struct buffer_head *ref_root_bh,
				     struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret = 0;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)fe_bh->b_data;
	struct buffer_head *blk_bh = NULL;

	if (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL) {
		ret = ocfs2_xattr_inline_attach_refcount(inode, fe_bh,
							 ref_ci, ref_root_bh,
							 dealloc);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	if (!di->i_xattr_loc)
		goto out;

	ret = ocfs2_read_xattr_block(inode, le64_to_cpu(di->i_xattr_loc),
				     &blk_bh);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_xattr_block_attach_refcount(inode, blk_bh, ref_ci,
						ref_root_bh, dealloc);
	if (ret)
		mlog_errno(ret);

	brelse(blk_bh);
out:

	return ret;
}