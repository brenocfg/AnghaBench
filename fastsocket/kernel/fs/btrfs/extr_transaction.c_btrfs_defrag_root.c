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
struct btrfs_trans_handle {unsigned long blocks_used; } ;
struct btrfs_root {scalar_t__ defrag_running; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_root; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_btree_balance_dirty (int /*<<< orphan*/ ,unsigned long) ; 
 int btrfs_defrag_leaves (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 scalar_t__ btrfs_fs_closing (struct btrfs_fs_info*) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ xchg (scalar_t__*,int) ; 

int btrfs_defrag_root(struct btrfs_root *root, int cacheonly)
{
	struct btrfs_fs_info *info = root->fs_info;
	struct btrfs_trans_handle *trans;
	int ret;
	unsigned long nr;

	if (xchg(&root->defrag_running, 1))
		return 0;

	while (1) {
		trans = btrfs_start_transaction(root, 0);
		if (IS_ERR(trans))
			return PTR_ERR(trans);

		ret = btrfs_defrag_leaves(trans, root, cacheonly);

		nr = trans->blocks_used;
		btrfs_end_transaction(trans, root);
		btrfs_btree_balance_dirty(info->tree_root, nr);
		cond_resched();

		if (btrfs_fs_closing(root->fs_info) || ret != -EAGAIN)
			break;
	}
	root->defrag_running = 0;
	return ret;
}