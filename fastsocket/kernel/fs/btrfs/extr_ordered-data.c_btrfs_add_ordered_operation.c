#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  ordered_operations; int /*<<< orphan*/  last_trans; int /*<<< orphan*/  generation; } ;
struct TYPE_5__ {scalar_t__ last_trans_committed; int /*<<< orphan*/  ordered_extent_lock; int /*<<< orphan*/  ordered_operations; TYPE_1__* running_transaction; } ;
struct TYPE_4__ {scalar_t__ blocked; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_range (struct inode*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_add_ordered_operation(struct btrfs_trans_handle *trans,
				 struct btrfs_root *root, struct inode *inode)
{
	u64 last_mod;

	last_mod = max(BTRFS_I(inode)->generation, BTRFS_I(inode)->last_trans);

	/*
	 * if this file hasn't been changed since the last transaction
	 * commit, we can safely return without doing anything
	 */
	if (last_mod < root->fs_info->last_trans_committed)
		return;

	/*
	 * the transaction is already committing.  Just start the IO and
	 * don't bother with all of this list nonsense
	 */
	if (trans && root->fs_info->running_transaction->blocked) {
		btrfs_wait_ordered_range(inode, 0, (u64)-1);
		return;
	}

	spin_lock(&root->fs_info->ordered_extent_lock);
	if (list_empty(&BTRFS_I(inode)->ordered_operations)) {
		list_add_tail(&BTRFS_I(inode)->ordered_operations,
			      &root->fs_info->ordered_operations);
	}
	spin_unlock(&root->fs_info->ordered_extent_lock);
}