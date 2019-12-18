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
struct ocfs2_refcount_rec {int /*<<< orphan*/  r_refcount; int /*<<< orphan*/  r_clusters; int /*<<< orphan*/  r_cpos; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,unsigned int,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_cache_cluster_dealloc (struct ocfs2_cached_dealloc_ctxt*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (struct super_block*,unsigned int) ; 
 int ocfs2_decrease_refcount_rec (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,int,unsigned int,unsigned int,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int ocfs2_get_refcount_rec (struct ocfs2_caching_info*,struct buffer_head*,unsigned int,unsigned int,struct ocfs2_refcount_rec*,int*,struct buffer_head**) ; 
 struct super_block* ocfs2_metadata_cache_get_super (struct ocfs2_caching_info*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 

__attribute__((used)) static int __ocfs2_decrease_refcount(handle_t *handle,
				     struct ocfs2_caching_info *ci,
				     struct buffer_head *ref_root_bh,
				     u64 cpos, u32 len,
				     struct ocfs2_alloc_context *meta_ac,
				     struct ocfs2_cached_dealloc_ctxt *dealloc,
				     int delete)
{
	int ret = 0, index = 0;
	struct ocfs2_refcount_rec rec;
	unsigned int r_count = 0, r_len;
	struct super_block *sb = ocfs2_metadata_cache_get_super(ci);
	struct buffer_head *ref_leaf_bh = NULL;

	mlog(0, "Tree owner %llu, decrease refcount start %llu, "
	     "len %u, delete %u\n",
	     (unsigned long long)ocfs2_metadata_cache_owner(ci),
	     (unsigned long long)cpos, len, delete);

	while (len) {
		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, len, &rec, &index,
					     &ref_leaf_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		r_count = le32_to_cpu(rec.r_refcount);
		BUG_ON(r_count == 0);
		if (!delete)
			BUG_ON(r_count > 1);

		r_len = min((u64)(cpos + len), le64_to_cpu(rec.r_cpos) +
			      le32_to_cpu(rec.r_clusters)) - cpos;

		ret = ocfs2_decrease_refcount_rec(handle, ci, ref_root_bh,
						  ref_leaf_bh, index,
						  cpos, r_len,
						  meta_ac, dealloc);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		if (le32_to_cpu(rec.r_refcount) == 1 && delete) {
			ret = ocfs2_cache_cluster_dealloc(dealloc,
					  ocfs2_clusters_to_blocks(sb, cpos),
							  r_len);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}
		}

		cpos += r_len;
		len -= r_len;
		brelse(ref_leaf_bh);
		ref_leaf_bh = NULL;
	}

out:
	brelse(ref_leaf_bh);
	return ret;
}