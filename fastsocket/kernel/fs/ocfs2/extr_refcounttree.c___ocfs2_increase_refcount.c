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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ocfs2_refcount_rec {void* r_refcount; int /*<<< orphan*/  r_cpos; void* r_clusters; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  le32_add_cpu (void**,int) ; 
 int le32_to_cpu (void*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_change_refcount_rec (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int,int,int) ; 
 int ocfs2_get_refcount_rec (struct ocfs2_caching_info*,struct buffer_head*,scalar_t__,int,struct ocfs2_refcount_rec*,int*,struct buffer_head**) ; 
 int ocfs2_insert_refcount_rec (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,struct ocfs2_refcount_rec*,int,int,struct ocfs2_alloc_context*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 
 int ocfs2_split_refcount_rec (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,struct buffer_head*,struct ocfs2_refcount_rec*,int,int,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 

__attribute__((used)) static int __ocfs2_increase_refcount(handle_t *handle,
				     struct ocfs2_caching_info *ci,
				     struct buffer_head *ref_root_bh,
				     u64 cpos, u32 len, int merge,
				     struct ocfs2_alloc_context *meta_ac,
				     struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret = 0, index;
	struct buffer_head *ref_leaf_bh = NULL;
	struct ocfs2_refcount_rec rec;
	unsigned int set_len = 0;

	mlog(0, "Tree owner %llu, add refcount start %llu, len %u\n",
	     (unsigned long long)ocfs2_metadata_cache_owner(ci),
	     (unsigned long long)cpos, len);

	while (len) {
		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, len, &rec, &index,
					     &ref_leaf_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		set_len = le32_to_cpu(rec.r_clusters);

		/*
		 * Here we may meet with 3 situations:
		 *
		 * 1. If we find an already existing record, and the length
		 *    is the same, cool, we just need to increase the r_refcount
		 *    and it is OK.
		 * 2. If we find a hole, just insert it with r_refcount = 1.
		 * 3. If we are in the middle of one extent record, split
		 *    it.
		 */
		if (rec.r_refcount && le64_to_cpu(rec.r_cpos) == cpos &&
		    set_len <= len) {
			mlog(0, "increase refcount rec, start %llu, len %u, "
			     "count %u\n", (unsigned long long)cpos, set_len,
			     le32_to_cpu(rec.r_refcount));
			ret = ocfs2_change_refcount_rec(handle, ci,
							ref_leaf_bh, index,
							merge, 1);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}
		} else if (!rec.r_refcount) {
			rec.r_refcount = cpu_to_le32(1);

			mlog(0, "insert refcount rec, start %llu, len %u\n",
			     (unsigned long long)le64_to_cpu(rec.r_cpos),
			     set_len);
			ret = ocfs2_insert_refcount_rec(handle, ci, ref_root_bh,
							ref_leaf_bh,
							&rec, index,
							merge, meta_ac);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}
		} else  {
			set_len = min((u64)(cpos + len),
				      le64_to_cpu(rec.r_cpos) + set_len) - cpos;
			rec.r_cpos = cpu_to_le64(cpos);
			rec.r_clusters = cpu_to_le32(set_len);
			le32_add_cpu(&rec.r_refcount, 1);

			mlog(0, "split refcount rec, start %llu, "
			     "len %u, count %u\n",
			     (unsigned long long)le64_to_cpu(rec.r_cpos),
			     set_len, le32_to_cpu(rec.r_refcount));
			ret = ocfs2_split_refcount_rec(handle, ci,
						       ref_root_bh, ref_leaf_bh,
						       &rec, index, merge,
						       meta_ac, dealloc);
			if (ret) {
				mlog_errno(ret);
				goto out;
			}
		}

		cpos += set_len;
		len -= set_len;
		brelse(ref_leaf_bh);
		ref_leaf_bh = NULL;
	}

out:
	brelse(ref_leaf_bh);
	return ret;
}