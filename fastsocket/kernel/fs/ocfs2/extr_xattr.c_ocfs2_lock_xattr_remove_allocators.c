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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_xattr_value_root {int /*<<< orphan*/  xr_list; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 unsigned int OCFS2_EXT_REFCOUNTED ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_refcounted_xattr_delete_need (struct inode*,struct ocfs2_caching_info*,struct buffer_head*,struct ocfs2_xattr_value_root*,int*,int*) ; 
 int ocfs2_reserve_new_metadata_blocks (int /*<<< orphan*/ ,int,struct ocfs2_alloc_context**) ; 
 int ocfs2_xattr_get_clusters (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int ocfs2_lock_xattr_remove_allocators(struct inode *inode,
					struct ocfs2_xattr_value_root *xv,
					struct ocfs2_caching_info *ref_ci,
					struct buffer_head *ref_root_bh,
					struct ocfs2_alloc_context **meta_ac,
					int *ref_credits)
{
	int ret, meta_add = 0;
	u32 p_cluster, num_clusters;
	unsigned int ext_flags;

	*ref_credits = 0;
	ret = ocfs2_xattr_get_clusters(inode, 0, &p_cluster,
				       &num_clusters,
				       &xv->xr_list,
				       &ext_flags);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (!(ext_flags & OCFS2_EXT_REFCOUNTED))
		goto out;

	ret = ocfs2_refcounted_xattr_delete_need(inode, ref_ci,
						 ref_root_bh, xv,
						 &meta_add, ref_credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_reserve_new_metadata_blocks(OCFS2_SB(inode->i_sb),
						meta_add, meta_ac);
	if (ret)
		mlog_errno(ret);

out:
	return ret;
}