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
struct ocfs2_extent_tree {struct ocfs2_extent_list* et_root_el; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_tree_depth; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_add_branch (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct buffer_head*,struct buffer_head**,struct ocfs2_alloc_context*) ; 
 int ocfs2_find_branch_target (struct ocfs2_extent_tree*,struct buffer_head**) ; 
 int ocfs2_shift_tree_depth (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_alloc_context*,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_grow_tree(handle_t *handle, struct ocfs2_extent_tree *et,
			   int *final_depth, struct buffer_head **last_eb_bh,
			   struct ocfs2_alloc_context *meta_ac)
{
	int ret, shift;
	struct ocfs2_extent_list *el = et->et_root_el;
	int depth = le16_to_cpu(el->l_tree_depth);
	struct buffer_head *bh = NULL;

	BUG_ON(meta_ac == NULL);

	shift = ocfs2_find_branch_target(et, &bh);
	if (shift < 0) {
		ret = shift;
		mlog_errno(ret);
		goto out;
	}

	/* We traveled all the way to the bottom of the allocation tree
	 * and didn't find room for any more extents - we need to add
	 * another tree level */
	if (shift) {
		BUG_ON(bh);
		mlog(0, "need to shift tree depth (current = %d)\n", depth);

		/* ocfs2_shift_tree_depth will return us a buffer with
		 * the new extent block (so we can pass that to
		 * ocfs2_add_branch). */
		ret = ocfs2_shift_tree_depth(handle, et, meta_ac, &bh);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}
		depth++;
		if (depth == 1) {
			/*
			 * Special case: we have room now if we shifted from
			 * tree_depth 0, so no more work needs to be done.
			 *
			 * We won't be calling add_branch, so pass
			 * back *last_eb_bh as the new leaf. At depth
			 * zero, it should always be null so there's
			 * no reason to brelse.
			 */
			BUG_ON(*last_eb_bh);
			get_bh(bh);
			*last_eb_bh = bh;
			goto out;
		}
	}

	/* call ocfs2_add_branch to add the final part of the tree with
	 * the new data. */
	mlog(0, "add branch. bh = %p\n", bh);
	ret = ocfs2_add_branch(handle, et, bh, last_eb_bh,
			       meta_ac);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

out:
	if (final_depth)
		*final_depth = depth;
	brelse(bh);
	return ret;
}