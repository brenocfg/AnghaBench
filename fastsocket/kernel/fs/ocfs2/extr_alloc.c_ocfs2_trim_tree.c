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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ocfs2_truncate_context {int /*<<< orphan*/  tc_dealloc; } ;
struct ocfs2_path {int p_tree_depth; TYPE_1__* p_node; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_blkno; int /*<<< orphan*/  e_cpos; int /*<<< orphan*/  e_int_clusters; int /*<<< orphan*/  e_leaf_clusters; int /*<<< orphan*/  e_flags; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; int /*<<< orphan*/  l_tree_depth; } ;
struct ocfs2_extent_block {int /*<<< orphan*/  h_blkno; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {scalar_t__ b_data; scalar_t__ b_blocknr; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {struct ocfs2_extent_list* el; struct buffer_head* bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EROFS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_extent_rec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_cache_extent_block_free (int /*<<< orphan*/ *,struct ocfs2_extent_block*) ; 
 int ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ ocfs2_is_empty_extent (struct ocfs2_extent_rec*) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_rec_clusters (struct ocfs2_extent_list*,struct ocfs2_extent_rec*) ; 
 int /*<<< orphan*/  ocfs2_remove_from_cache (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static int ocfs2_trim_tree(struct inode *inode, struct ocfs2_path *path,
			   handle_t *handle, struct ocfs2_truncate_context *tc,
			   u32 clusters_to_del, u64 *delete_start, u8 *flags)
{
	int ret, i, index = path->p_tree_depth;
	u32 new_edge = 0;
	u64 deleted_eb = 0;
	struct buffer_head *bh;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_rec *rec;

	*delete_start = 0;
	*flags = 0;

	while (index >= 0) {
		bh = path->p_node[index].bh;
		el = path->p_node[index].el;

		mlog(0, "traveling tree (index = %d, block = %llu)\n",
		     index,  (unsigned long long)bh->b_blocknr);

		BUG_ON(le16_to_cpu(el->l_next_free_rec) == 0);

		if (index !=
		    (path->p_tree_depth - le16_to_cpu(el->l_tree_depth))) {
			ocfs2_error(inode->i_sb,
				    "Inode %lu has invalid ext. block %llu",
				    inode->i_ino,
				    (unsigned long long)bh->b_blocknr);
			ret = -EROFS;
			goto out;
		}

find_tail_record:
		i = le16_to_cpu(el->l_next_free_rec) - 1;
		rec = &el->l_recs[i];

		mlog(0, "Extent list before: record %d: (%u, %u, %llu), "
		     "next = %u\n", i, le32_to_cpu(rec->e_cpos),
		     ocfs2_rec_clusters(el, rec),
		     (unsigned long long)le64_to_cpu(rec->e_blkno),
		     le16_to_cpu(el->l_next_free_rec));

		BUG_ON(ocfs2_rec_clusters(el, rec) < clusters_to_del);

		if (le16_to_cpu(el->l_tree_depth) == 0) {
			/*
			 * If the leaf block contains a single empty
			 * extent and no records, we can just remove
			 * the block.
			 */
			if (i == 0 && ocfs2_is_empty_extent(rec)) {
				memset(rec, 0,
				       sizeof(struct ocfs2_extent_rec));
				el->l_next_free_rec = cpu_to_le16(0);

				goto delete;
			}

			/*
			 * Remove any empty extents by shifting things
			 * left. That should make life much easier on
			 * the code below. This condition is rare
			 * enough that we shouldn't see a performance
			 * hit.
			 */
			if (ocfs2_is_empty_extent(&el->l_recs[0])) {
				le16_add_cpu(&el->l_next_free_rec, -1);

				for(i = 0;
				    i < le16_to_cpu(el->l_next_free_rec); i++)
					el->l_recs[i] = el->l_recs[i + 1];

				memset(&el->l_recs[i], 0,
				       sizeof(struct ocfs2_extent_rec));

				/*
				 * We've modified our extent list. The
				 * simplest way to handle this change
				 * is to being the search from the
				 * start again.
				 */
				goto find_tail_record;
			}

			le16_add_cpu(&rec->e_leaf_clusters, -clusters_to_del);

			/*
			 * We'll use "new_edge" on our way back up the
			 * tree to know what our rightmost cpos is.
			 */
			new_edge = le16_to_cpu(rec->e_leaf_clusters);
			new_edge += le32_to_cpu(rec->e_cpos);

			/*
			 * The caller will use this to delete data blocks.
			 */
			*delete_start = le64_to_cpu(rec->e_blkno)
				+ ocfs2_clusters_to_blocks(inode->i_sb,
					le16_to_cpu(rec->e_leaf_clusters));
			*flags = rec->e_flags;

			/*
			 * If it's now empty, remove this record.
			 */
			if (le16_to_cpu(rec->e_leaf_clusters) == 0) {
				memset(rec, 0,
				       sizeof(struct ocfs2_extent_rec));
				le16_add_cpu(&el->l_next_free_rec, -1);
			}
		} else {
			if (le64_to_cpu(rec->e_blkno) == deleted_eb) {
				memset(rec, 0,
				       sizeof(struct ocfs2_extent_rec));
				le16_add_cpu(&el->l_next_free_rec, -1);

				goto delete;
			}

			/* Can this actually happen? */
			if (le16_to_cpu(el->l_next_free_rec) == 0)
				goto delete;

			/*
			 * We never actually deleted any clusters
			 * because our leaf was empty. There's no
			 * reason to adjust the rightmost edge then.
			 */
			if (new_edge == 0)
				goto delete;

			rec->e_int_clusters = cpu_to_le32(new_edge);
			le32_add_cpu(&rec->e_int_clusters,
				     -le32_to_cpu(rec->e_cpos));

			 /*
			  * A deleted child record should have been
			  * caught above.
			  */
			 BUG_ON(le32_to_cpu(rec->e_int_clusters) == 0);
		}

delete:
		ret = ocfs2_journal_dirty(handle, bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		mlog(0, "extent list container %llu, after: record %d: "
		     "(%u, %u, %llu), next = %u.\n",
		     (unsigned long long)bh->b_blocknr, i,
		     le32_to_cpu(rec->e_cpos), ocfs2_rec_clusters(el, rec),
		     (unsigned long long)le64_to_cpu(rec->e_blkno),
		     le16_to_cpu(el->l_next_free_rec));

		/*
		 * We must be careful to only attempt delete of an
		 * extent block (and not the root inode block).
		 */
		if (index > 0 && le16_to_cpu(el->l_next_free_rec) == 0) {
			struct ocfs2_extent_block *eb =
				(struct ocfs2_extent_block *)bh->b_data;

			/*
			 * Save this for use when processing the
			 * parent block.
			 */
			deleted_eb = le64_to_cpu(eb->h_blkno);

			mlog(0, "deleting this extent block.\n");

			ocfs2_remove_from_cache(INODE_CACHE(inode), bh);

			BUG_ON(ocfs2_rec_clusters(el, &el->l_recs[0]));
			BUG_ON(le32_to_cpu(el->l_recs[0].e_cpos));
			BUG_ON(le64_to_cpu(el->l_recs[0].e_blkno));

			ret = ocfs2_cache_extent_block_free(&tc->tc_dealloc, eb);
			/* An error here is not fatal. */
			if (ret < 0)
				mlog_errno(ret);
		} else {
			deleted_eb = 0;
		}

		index--;
	}

	ret = 0;
out:
	return ret;
}