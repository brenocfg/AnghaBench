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
struct ocfs2_caching_info {int ci_flags; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int OCFS2_CACHE_FL_INLINE ; 
 int /*<<< orphan*/  __ocfs2_set_buffer_uptodate (struct ocfs2_caching_info*,scalar_t__,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_append_cache_array (struct ocfs2_caching_info*,scalar_t__) ; 
 scalar_t__ ocfs2_buffer_cached (struct ocfs2_caching_info*,struct buffer_head*) ; 
 scalar_t__ ocfs2_insert_can_use_array (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_lock (struct ocfs2_caching_info*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_unlock (struct ocfs2_caching_info*) ; 

void ocfs2_set_buffer_uptodate(struct ocfs2_caching_info *ci,
			       struct buffer_head *bh)
{
	int expand;

	/* The block may very well exist in our cache already, so avoid
	 * doing any more work in that case. */
	if (ocfs2_buffer_cached(ci, bh))
		return;

	mlog(0, "Owner %llu, inserting block %llu\n",
	     (unsigned long long)ocfs2_metadata_cache_owner(ci),
	     (unsigned long long)bh->b_blocknr);

	/* No need to recheck under spinlock - insertion is guarded by
	 * co_io_lock() */
	ocfs2_metadata_cache_lock(ci);
	if (ocfs2_insert_can_use_array(ci)) {
		/* Fast case - it's an array and there's a free
		 * spot. */
		ocfs2_append_cache_array(ci, bh->b_blocknr);
		ocfs2_metadata_cache_unlock(ci);
		return;
	}

	expand = 0;
	if (ci->ci_flags & OCFS2_CACHE_FL_INLINE) {
		/* We need to bump things up to a tree. */
		expand = 1;
	}
	ocfs2_metadata_cache_unlock(ci);

	__ocfs2_set_buffer_uptodate(ci, bh->b_blocknr, expand);
}