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
struct ocfs2_super {int dummy; } ;
struct ocfs2_post_refcount {int (* func ) (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  para; scalar_t__ credits; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ocfs2_increase_refcount (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_calc_refcount_meta_credits (int /*<<< orphan*/ ,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_mark_extent_refcounted (struct inode*,struct ocfs2_extent_tree*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 
 int stub1 (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ocfs2_add_refcount_flag(struct inode *inode,
			    struct ocfs2_extent_tree *data_et,
			    struct ocfs2_caching_info *ref_ci,
			    struct buffer_head *ref_root_bh,
			    u32 cpos, u32 p_cluster, u32 num_clusters,
			    struct ocfs2_cached_dealloc_ctxt *dealloc,
			    struct ocfs2_post_refcount *post)
{
	int ret;
	handle_t *handle;
	int credits = 1, ref_blocks = 0;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_alloc_context *meta_ac = NULL;

	ret = ocfs2_calc_refcount_meta_credits(inode->i_sb,
					       ref_ci, ref_root_bh,
					       p_cluster, num_clusters,
					       &ref_blocks, &credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	mlog(0, "reserve new metadata %d, credits = %d\n",
	     ref_blocks, credits);

	if (ref_blocks) {
		ret = ocfs2_reserve_new_metadata_blocks(OCFS2_SB(inode->i_sb),
							ref_blocks, &meta_ac);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	}

	if (post)
		credits += post->credits;

	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_mark_extent_refcounted(inode, data_et, handle,
					   cpos, num_clusters, p_cluster,
					   meta_ac, dealloc);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ret = __ocfs2_increase_refcount(handle, ref_ci, ref_root_bh,
					p_cluster, num_clusters, 0,
					meta_ac, dealloc);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	if (post && post->func) {
		ret = post->func(inode, handle, post->para);
		if (ret)
			mlog_errno(ret);
	}

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	if (meta_ac)
		ocfs2_free_alloc_context(meta_ac);
	return ret;
}