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
struct ulist {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int find_parent_nodes (struct btrfs_trans_handle*,struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ulist*,struct ulist*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free_leaf_list (struct ulist*) ; 
 struct ulist* ulist_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulist_free (struct ulist*) ; 

__attribute__((used)) static int btrfs_find_all_leafs(struct btrfs_trans_handle *trans,
				struct btrfs_fs_info *fs_info, u64 bytenr,
				u64 delayed_ref_seq, u64 time_seq,
				struct ulist **leafs,
				const u64 *extent_item_pos)
{
	struct ulist *tmp;
	int ret;

	tmp = ulist_alloc(GFP_NOFS);
	if (!tmp)
		return -ENOMEM;
	*leafs = ulist_alloc(GFP_NOFS);
	if (!*leafs) {
		ulist_free(tmp);
		return -ENOMEM;
	}

	ret = find_parent_nodes(trans, fs_info, bytenr, delayed_ref_seq,
				time_seq, *leafs, tmp, extent_item_pos);
	ulist_free(tmp);

	if (ret < 0 && ret != -ENOENT) {
		free_leaf_list(*leafs);
		return ret;
	}

	return 0;
}