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
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
struct super_block {int dummy; } ;
struct ocfs2_refcount_rec {int dummy; } ;
struct ocfs2_extent_list {struct ocfs2_extent_rec* l_recs; int /*<<< orphan*/  l_next_free_rec; scalar_t__ l_tree_depth; } ;
struct ocfs2_refcount_block {struct ocfs2_extent_list rf_list; int /*<<< orphan*/  rf_flags; } ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_blkno; int /*<<< orphan*/  e_cpos; } ;
struct ocfs2_extent_block {struct ocfs2_extent_list h_list; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;

/* Variables and functions */
 int EROFS ; 
 unsigned int OCFS2_32BIT_POS_MASK ; 
 unsigned int OCFS2_REFCOUNT_TREE_FL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_error (struct super_block*,char*,unsigned long long,unsigned long long) ; 
 int ocfs2_find_leaf (struct ocfs2_caching_info*,struct ocfs2_extent_list*,unsigned int,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_find_refcount_rec_in_rl (struct ocfs2_caching_info*,struct buffer_head*,unsigned int,unsigned int,struct ocfs2_refcount_rec*,int*) ; 
 struct super_block* ocfs2_metadata_cache_get_super (struct ocfs2_caching_info*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 
 int ocfs2_read_refcount_block (struct ocfs2_caching_info*,int /*<<< orphan*/ ,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_get_refcount_rec(struct ocfs2_caching_info *ci,
				  struct buffer_head *ref_root_bh,
				  u64 cpos, unsigned int len,
				  struct ocfs2_refcount_rec *ret_rec,
				  int *index,
				  struct buffer_head **ret_bh)
{
	int ret = 0, i, found;
	u32 low_cpos;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_rec *tmp, *rec = NULL;
	struct ocfs2_extent_block *eb;
	struct buffer_head *eb_bh = NULL, *ref_leaf_bh = NULL;
	struct super_block *sb = ocfs2_metadata_cache_get_super(ci);
	struct ocfs2_refcount_block *rb =
			(struct ocfs2_refcount_block *)ref_root_bh->b_data;

	if (!(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL)) {
		ocfs2_find_refcount_rec_in_rl(ci, ref_root_bh, cpos, len,
					      ret_rec, index);
		*ret_bh = ref_root_bh;
		get_bh(ref_root_bh);
		return 0;
	}

	el = &rb->rf_list;
	low_cpos = cpos & OCFS2_32BIT_POS_MASK;

	if (el->l_tree_depth) {
		ret = ocfs2_find_leaf(ci, el, low_cpos, &eb_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		eb = (struct ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;

		if (el->l_tree_depth) {
			ocfs2_error(sb,
			"refcount tree %llu has non zero tree "
			"depth in leaf btree tree block %llu\n",
			(unsigned long long)ocfs2_metadata_cache_owner(ci),
			(unsigned long long)eb_bh->b_blocknr);
			ret = -EROFS;
			goto out;
		}
	}

	found = 0;
	for (i = le16_to_cpu(el->l_next_free_rec) - 1; i >= 0; i--) {
		rec = &el->l_recs[i];

		if (le32_to_cpu(rec->e_cpos) <= low_cpos) {
			found = 1;
			break;
		}
	}

	/* adjust len when we have ocfs2_extent_rec after it. */
	if (found && i < le16_to_cpu(el->l_next_free_rec) - 1) {
		tmp = &el->l_recs[i+1];

		if (le32_to_cpu(tmp->e_cpos) < cpos + len)
			len = le32_to_cpu(tmp->e_cpos) - cpos;
	}

	ret = ocfs2_read_refcount_block(ci, le64_to_cpu(rec->e_blkno),
					&ref_leaf_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ocfs2_find_refcount_rec_in_rl(ci, ref_leaf_bh, cpos, len,
				      ret_rec, index);
	*ret_bh = ref_leaf_bh;
out:
	brelse(eb_bh);
	return ret;
}