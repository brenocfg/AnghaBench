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
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_expand_inline_ref_root (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head**,struct ocfs2_alloc_context*) ; 
 int ocfs2_new_leaf_refcount_block (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,struct ocfs2_alloc_context*) ; 

__attribute__((used)) static int ocfs2_expand_refcount_tree(handle_t *handle,
				      struct ocfs2_caching_info *ci,
				      struct buffer_head *ref_root_bh,
				      struct buffer_head *ref_leaf_bh,
				      struct ocfs2_alloc_context *meta_ac)
{
	int ret;
	struct buffer_head *expand_bh = NULL;

	if (ref_root_bh == ref_leaf_bh) {
		/*
		 * the old root bh hasn't been expanded to a b-tree,
		 * so expand it first.
		 */
		ret = ocfs2_expand_inline_ref_root(handle, ci, ref_root_bh,
						   &expand_bh, meta_ac);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}
	} else {
		expand_bh = ref_leaf_bh;
		get_bh(expand_bh);
	}


	/* Now add a new refcount block into the tree.*/
	ret = ocfs2_new_leaf_refcount_block(handle, ci, ref_root_bh,
					    expand_bh, meta_ac);
	if (ret)
		mlog_errno(ret);
out:
	brelse(expand_bh);
	return ret;
}