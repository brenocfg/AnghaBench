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
struct btrfs_trans_handle {int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/  bytes_reserved; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_2__ {scalar_t__ enospc_unlink; int /*<<< orphan*/  trans_block_rsv; int /*<<< orphan*/  global_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btrfs_block_rsv_release (struct btrfs_root*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 

__attribute__((used)) static void __unlink_end_trans(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root)
{
	if (trans->block_rsv == &root->fs_info->global_block_rsv) {
		btrfs_block_rsv_release(root, trans->block_rsv,
					trans->bytes_reserved);
		trans->block_rsv = &root->fs_info->trans_block_rsv;
		BUG_ON(!root->fs_info->enospc_unlink);
		root->fs_info->enospc_unlink = 0;
	}
	btrfs_end_transaction(trans, root);
}