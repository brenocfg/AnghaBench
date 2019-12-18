#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_3__ {scalar_t__ logical; } ;
struct tree_mod_elem {scalar_t__ op; TYPE_1__ old_root; } ;
struct btrfs_root {TYPE_2__* node; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MOD_LOG_ROOT_REPLACE ; 
 struct tree_mod_elem* tree_mod_log_search_oldest (struct btrfs_fs_info*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct tree_mod_elem *
__tree_mod_log_oldest_root(struct btrfs_fs_info *fs_info,
			   struct btrfs_root *root, u64 time_seq)
{
	struct tree_mod_elem *tm;
	struct tree_mod_elem *found = NULL;
	u64 root_logical = root->node->start;
	int looped = 0;

	if (!time_seq)
		return 0;

	/*
	 * the very last operation that's logged for a root is the replacement
	 * operation (if it is replaced at all). this has the index of the *new*
	 * root, making it the very first operation that's logged for this root.
	 */
	while (1) {
		tm = tree_mod_log_search_oldest(fs_info, root_logical,
						time_seq);
		if (!looped && !tm)
			return 0;
		/*
		 * if there are no tree operation for the oldest root, we simply
		 * return it. this should only happen if that (old) root is at
		 * level 0.
		 */
		if (!tm)
			break;

		/*
		 * if there's an operation that's not a root replacement, we
		 * found the oldest version of our root. normally, we'll find a
		 * MOD_LOG_KEY_REMOVE_WHILE_FREEING operation here.
		 */
		if (tm->op != MOD_LOG_ROOT_REPLACE)
			break;

		found = tm;
		root_logical = tm->old_root.logical;
		BUG_ON(root_logical == root->node->start);
		looped = 1;
	}

	/* if there's no old root to return, return what we found instead */
	if (!found)
		found = tm;

	return found;
}