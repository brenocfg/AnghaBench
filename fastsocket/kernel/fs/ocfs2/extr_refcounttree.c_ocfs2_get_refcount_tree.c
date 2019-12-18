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
struct ocfs2_super {int /*<<< orphan*/  osb_lock; struct ocfs2_refcount_tree* osb_ref_tree_lru; } ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_ci; int /*<<< orphan*/  rf_generation; int /*<<< orphan*/  rf_blkno; } ;
struct ocfs2_refcount_block {int /*<<< orphan*/  rf_generation; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct ocfs2_refcount_tree* ocfs2_allocate_refcount_tree (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 struct ocfs2_refcount_tree* ocfs2_find_refcount_tree (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_refcount_tree (struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  ocfs2_init_refcount_tree_lock (struct ocfs2_super*,struct ocfs2_refcount_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_insert_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_purge (int /*<<< orphan*/ *) ; 
 int ocfs2_read_refcount_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_get_refcount_tree(struct ocfs2_super *osb, u64 rf_blkno,
				   struct ocfs2_refcount_tree **ret_tree)
{
	int ret = 0;
	struct ocfs2_refcount_tree *tree, *new = NULL;
	struct buffer_head *ref_root_bh = NULL;
	struct ocfs2_refcount_block *ref_rb;

	spin_lock(&osb->osb_lock);
	if (osb->osb_ref_tree_lru &&
	    osb->osb_ref_tree_lru->rf_blkno == rf_blkno)
		tree = osb->osb_ref_tree_lru;
	else
		tree = ocfs2_find_refcount_tree(osb, rf_blkno);
	if (tree)
		goto out;

	spin_unlock(&osb->osb_lock);

	new = ocfs2_allocate_refcount_tree(osb, rf_blkno);
	if (!new) {
		ret = -ENOMEM;
		mlog_errno(ret);
		return ret;
	}
	/*
	 * We need the generation to create the refcount tree lock and since
	 * it isn't changed during the tree modification, we are safe here to
	 * read without protection.
	 * We also have to purge the cache after we create the lock since the
	 * refcount block may have the stale data. It can only be trusted when
	 * we hold the refcount lock.
	 */
	ret = ocfs2_read_refcount_block(&new->rf_ci, rf_blkno, &ref_root_bh);
	if (ret) {
		mlog_errno(ret);
		ocfs2_metadata_cache_exit(&new->rf_ci);
		kfree(new);
		return ret;
	}

	ref_rb = (struct ocfs2_refcount_block *)ref_root_bh->b_data;
	new->rf_generation = le32_to_cpu(ref_rb->rf_generation);
	ocfs2_init_refcount_tree_lock(osb, new, rf_blkno,
				      new->rf_generation);
	ocfs2_metadata_cache_purge(&new->rf_ci);

	spin_lock(&osb->osb_lock);
	tree = ocfs2_find_refcount_tree(osb, rf_blkno);
	if (tree)
		goto out;

	ocfs2_insert_refcount_tree(osb, new);

	tree = new;
	new = NULL;

out:
	*ret_tree = tree;

	osb->osb_ref_tree_lru = tree;

	spin_unlock(&osb->osb_lock);

	if (new)
		ocfs2_free_refcount_tree(new);

	brelse(ref_root_bh);
	return ret;
}