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
struct TYPE_2__ {int seq; scalar_t__ flags; } ;
struct tree_mod_elem {TYPE_1__ elem; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_mod_seq_lock; int /*<<< orphan*/  tree_mod_seq_list; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  __get_tree_mod_seq (struct btrfs_fs_info*,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct tree_mod_elem*) ; 
 struct tree_mod_elem* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tree_mod_dont_log (struct btrfs_fs_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int tree_mod_alloc(struct btrfs_fs_info *fs_info, gfp_t flags,
				 struct tree_mod_elem **tm_ret)
{
	struct tree_mod_elem *tm;
	int seq;

	if (tree_mod_dont_log(fs_info, NULL))
		return 0;

	tm = *tm_ret = kzalloc(sizeof(*tm), flags);
	if (!tm)
		return -ENOMEM;

	tm->elem.flags = 0;
	spin_lock(&fs_info->tree_mod_seq_lock);
	if (list_empty(&fs_info->tree_mod_seq_list)) {
		/*
		 * someone emptied the list while we were waiting for the lock.
		 * we must not add to the list, because no blocker exists. items
		 * are removed from the list only when the existing blocker is
		 * removed from the list.
		 */
		kfree(tm);
		seq = 0;
		spin_unlock(&fs_info->tree_mod_seq_lock);
	} else {
		__get_tree_mod_seq(fs_info, &tm->elem);
		seq = tm->elem.seq;
	}

	return seq;
}