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
struct rb_root {int dummy; } ;
struct TYPE_2__ {struct rb_root ci_tree; } ;
struct ocfs2_caching_info {int ci_flags; unsigned int ci_num_cached; TYPE_1__ ci_cache; int /*<<< orphan*/  ci_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_CACHE_FL_INLINE ; 
 struct rb_root RB_ROOT ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_lock (struct ocfs2_caching_info*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_reset (struct ocfs2_caching_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_unlock (struct ocfs2_caching_info*) ; 
 unsigned int ocfs2_purge_copied_metadata_tree (struct rb_root*) ; 

void ocfs2_metadata_cache_purge(struct ocfs2_caching_info *ci)
{
	unsigned int tree, to_purge, purged;
	struct rb_root root = RB_ROOT;

	BUG_ON(!ci || !ci->ci_ops);

	ocfs2_metadata_cache_lock(ci);
	tree = !(ci->ci_flags & OCFS2_CACHE_FL_INLINE);
	to_purge = ci->ci_num_cached;

	mlog(0, "Purge %u %s items from Owner %llu\n", to_purge,
	     tree ? "array" : "tree",
	     (unsigned long long)ocfs2_metadata_cache_owner(ci));

	/* If we're a tree, save off the root so that we can safely
	 * initialize the cache. We do the work to free tree members
	 * without the spinlock. */
	if (tree)
		root = ci->ci_cache.ci_tree;

	ocfs2_metadata_cache_reset(ci, 0);
	ocfs2_metadata_cache_unlock(ci);

	purged = ocfs2_purge_copied_metadata_tree(&root);
	/* If possible, track the number wiped so that we can more
	 * easily detect counting errors. Unfortunately, this is only
	 * meaningful for trees. */
	if (tree && purged != to_purge)
		mlog(ML_ERROR, "Owner %llu, count = %u, purged = %u\n",
		     (unsigned long long)ocfs2_metadata_cache_owner(ci),
		     to_purge, purged);
}