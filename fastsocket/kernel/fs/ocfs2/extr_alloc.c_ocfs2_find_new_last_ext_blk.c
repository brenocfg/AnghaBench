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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_path {int /*<<< orphan*/  p_tree_depth; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_leaf_clusters; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; } ;
struct ocfs2_extent_block {int /*<<< orphan*/  h_blkno; struct ocfs2_extent_list h_list; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {unsigned int ip_clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_EXTENT_BLOCK (struct ocfs2_extent_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_find_cpos_for_left_leaf (int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ *) ; 
 int ocfs2_find_leaf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 
 int /*<<< orphan*/  path_root_el (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_find_new_last_ext_blk(struct inode *inode,
				       unsigned int clusters_to_del,
				       struct ocfs2_path *path,
				       struct buffer_head **new_last_eb)
{
	int next_free, ret = 0;
	u32 cpos;
	struct ocfs2_extent_rec *rec;
	struct ocfs2_extent_block *eb;
	struct ocfs2_extent_list *el;
	struct buffer_head *bh = NULL;

	*new_last_eb = NULL;

	/* we have no tree, so of course, no last_eb. */
	if (!path->p_tree_depth)
		goto out;

	/* trunc to zero special case - this makes tree_depth = 0
	 * regardless of what it is.  */
	if (OCFS2_I(inode)->ip_clusters == clusters_to_del)
		goto out;

	el = path_leaf_el(path);
	BUG_ON(!el->l_next_free_rec);

	/*
	 * Make sure that this extent list will actually be empty
	 * after we clear away the data. We can shortcut out if
	 * there's more than one non-empty extent in the
	 * list. Otherwise, a check of the remaining extent is
	 * necessary.
	 */
	next_free = le16_to_cpu(el->l_next_free_rec);
	rec = NULL;
	if (ocfs2_is_empty_extent(&el->l_recs[0])) {
		if (next_free > 2)
			goto out;

		/* We may have a valid extent in index 1, check it. */
		if (next_free == 2)
			rec = &el->l_recs[1];

		/*
		 * Fall through - no more nonempty extents, so we want
		 * to delete this leaf.
		 */
	} else {
		if (next_free > 1)
			goto out;

		rec = &el->l_recs[0];
	}

	if (rec) {
		/*
		 * Check it we'll only be trimming off the end of this
		 * cluster.
		 */
		if (le16_to_cpu(rec->e_leaf_clusters) > clusters_to_del)
			goto out;
	}

	ret = ocfs2_find_cpos_for_left_leaf(inode->i_sb, path, &cpos);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_find_leaf(INODE_CACHE(inode), path_root_el(path), cpos, &bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	eb = (struct ocfs2_extent_block *) bh->b_data;
	el = &eb->h_list;

	/* ocfs2_find_leaf() gets the eb from ocfs2_read_extent_block().
	 * Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_EXTENT_BLOCK(eb));

	*new_last_eb = bh;
	get_bh(*new_last_eb);
	mlog(0, "returning block %llu, (cpos: %u)\n",
	     (unsigned long long)le64_to_cpu(eb->h_blkno), cpos);
out:
	brelse(bh);

	return ret;
}