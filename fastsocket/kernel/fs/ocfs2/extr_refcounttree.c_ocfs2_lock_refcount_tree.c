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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_refcount_tree {scalar_t__ rf_generation; int rf_removed; int /*<<< orphan*/  rf_blkno; int /*<<< orphan*/  rf_ci; } ;
struct ocfs2_refcount_block {int /*<<< orphan*/  rf_generation; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int __ocfs2_lock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_erase_refcount_tree_from_list (struct ocfs2_super*,struct ocfs2_refcount_tree*) ; 
 int ocfs2_get_refcount_tree (struct ocfs2_super*,int /*<<< orphan*/ ,struct ocfs2_refcount_tree**) ; 
 int ocfs2_read_refcount_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree_get (struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  ocfs2_refcount_tree_put (struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  ocfs2_unlock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 

int ocfs2_lock_refcount_tree(struct ocfs2_super *osb,
			     u64 ref_blkno, int rw,
			     struct ocfs2_refcount_tree **ret_tree,
			     struct buffer_head **ref_bh)
{
	int ret, delete_tree = 0;
	struct ocfs2_refcount_tree *tree = NULL;
	struct buffer_head *ref_root_bh = NULL;
	struct ocfs2_refcount_block *rb;

again:
	ret = ocfs2_get_refcount_tree(osb, ref_blkno, &tree);
	if (ret) {
		mlog_errno(ret);
		return ret;
	}

	ocfs2_refcount_tree_get(tree);

	ret = __ocfs2_lock_refcount_tree(osb, tree, rw);
	if (ret) {
		mlog_errno(ret);
		ocfs2_refcount_tree_put(tree);
		goto out;
	}

	ret = ocfs2_read_refcount_block(&tree->rf_ci, tree->rf_blkno,
					&ref_root_bh);
	if (ret) {
		mlog_errno(ret);
		ocfs2_unlock_refcount_tree(osb, tree, rw);
		ocfs2_refcount_tree_put(tree);
		goto out;
	}

	rb = (struct ocfs2_refcount_block *)ref_root_bh->b_data;
	/*
	 * If the refcount block has been freed and re-created, we may need
	 * to recreate the refcount tree also.
	 *
	 * Here we just remove the tree from the rb-tree, and the last
	 * kref holder will unlock and delete this refcount_tree.
	 * Then we goto "again" and ocfs2_get_refcount_tree will create
	 * the new refcount tree for us.
	 */
	if (tree->rf_generation != le32_to_cpu(rb->rf_generation)) {
		if (!tree->rf_removed) {
			ocfs2_erase_refcount_tree_from_list(osb, tree);
			tree->rf_removed = 1;
			delete_tree = 1;
		}

		ocfs2_unlock_refcount_tree(osb, tree, rw);
		/*
		 * We get an extra reference when we create the refcount
		 * tree, so another put will destroy it.
		 */
		if (delete_tree)
			ocfs2_refcount_tree_put(tree);
		brelse(ref_root_bh);
		ref_root_bh = NULL;
		goto again;
	}

	*ret_tree = tree;
	if (ref_bh) {
		*ref_bh = ref_root_bh;
		ref_root_bh = NULL;
	}
out:
	brelse(ref_root_bh);
	return ret;
}