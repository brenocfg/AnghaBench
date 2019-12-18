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
typedef  int u32 ;
struct ocfs2_xattr_value_root {int /*<<< orphan*/  xr_list; int /*<<< orphan*/  xr_clusters; } ;
struct ocfs2_refcount_rec {int /*<<< orphan*/  r_clusters; int /*<<< orphan*/  r_refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  rl_count; int /*<<< orphan*/  rl_used; } ;
struct ocfs2_refcount_block {int /*<<< orphan*/  rf_flags; TYPE_1__ rf_records; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_root_el; } ;
struct ocfs2_caching_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OCFS2_EXPAND_REFCOUNT_TREE_CREDITS ; 
 int OCFS2_REFCOUNT_TREE_FL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_calc_extend_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ocfs2_get_refcount_rec (struct ocfs2_caching_info*,struct buffer_head*,int,int,struct ocfs2_refcount_rec*,int*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_init_refcount_extent_tree (struct ocfs2_extent_tree*,struct ocfs2_caching_info*,struct buffer_head*) ; 
 int ocfs2_xattr_get_clusters (struct inode*,int,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ocfs2_refcounted_xattr_delete_need(struct inode *inode,
				       struct ocfs2_caching_info *ref_ci,
				       struct buffer_head *ref_root_bh,
				       struct ocfs2_xattr_value_root *xv,
				       int *meta_add, int *credits)
{
	int ret = 0, index, ref_blocks = 0;
	u32 p_cluster, num_clusters;
	u32 cpos = 0, clusters = le32_to_cpu(xv->xr_clusters);
	struct ocfs2_refcount_block *rb;
	struct ocfs2_refcount_rec rec;
	struct buffer_head *ref_leaf_bh = NULL;

	while (cpos < clusters) {
		ret = ocfs2_xattr_get_clusters(inode, cpos, &p_cluster,
					       &num_clusters, &xv->xr_list,
					       NULL);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		cpos += num_clusters;

		while (num_clusters) {
			ret = ocfs2_get_refcount_rec(ref_ci, ref_root_bh,
						     p_cluster, num_clusters,
						     &rec, &index,
						     &ref_leaf_bh);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}

			BUG_ON(!rec.r_refcount);

			rb = (struct ocfs2_refcount_block *)ref_leaf_bh->b_data;

			/*
			 * We really don't know whether the other clusters is in
			 * this refcount block or not, so just take the worst
			 * case that all the clusters are in this block and each
			 * one will split a refcount rec, so totally we need
			 * clusters * 2 new refcount rec.
			 */
			if (le64_to_cpu(rb->rf_records.rl_used) + clusters * 2 >
			    le16_to_cpu(rb->rf_records.rl_count))
				ref_blocks++;

			*credits += 1;
			brelse(ref_leaf_bh);
			ref_leaf_bh = NULL;

			if (num_clusters <= le32_to_cpu(rec.r_clusters))
				break;
			else
				num_clusters -= le32_to_cpu(rec.r_clusters);
			p_cluster += num_clusters;
		}
	}

	*meta_add += ref_blocks;
	if (!ref_blocks)
		goto out;

	rb = (struct ocfs2_refcount_block *)ref_root_bh->b_data;
	if (le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL)
		*credits += OCFS2_EXPAND_REFCOUNT_TREE_CREDITS;
	else {
		struct ocfs2_extent_tree et;

		ocfs2_init_refcount_extent_tree(&et, ref_ci, ref_root_bh);
		*credits += ocfs2_calc_extend_credits(inode->i_sb,
						      et.et_root_el,
						      ref_blocks);
	}

out:
	brelse(ref_leaf_bh);
	return ret;
}