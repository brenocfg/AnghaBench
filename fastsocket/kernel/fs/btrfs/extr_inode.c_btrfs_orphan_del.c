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
struct inode {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  orphan_inodes; int /*<<< orphan*/  orphan_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_HAS_ORPHAN_ITEM ; 
 int /*<<< orphan*/  BTRFS_INODE_ORPHAN_META_RESERVED ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int btrfs_del_orphan_item (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_ino (struct inode*) ; 
 int /*<<< orphan*/  btrfs_orphan_release_metadata (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_orphan_del(struct btrfs_trans_handle *trans, struct inode *inode)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int delete_item = 0;
	int release_rsv = 0;
	int ret = 0;

	spin_lock(&root->orphan_lock);
	if (test_and_clear_bit(BTRFS_INODE_HAS_ORPHAN_ITEM,
			       &BTRFS_I(inode)->runtime_flags))
		delete_item = 1;

	if (test_and_clear_bit(BTRFS_INODE_ORPHAN_META_RESERVED,
			       &BTRFS_I(inode)->runtime_flags))
		release_rsv = 1;
	spin_unlock(&root->orphan_lock);

	if (trans && delete_item) {
		ret = btrfs_del_orphan_item(trans, root, btrfs_ino(inode));
		BUG_ON(ret); /* -ENOMEM or corruption (JDM: Recheck) */
	}

	if (release_rsv) {
		btrfs_orphan_release_metadata(inode);
		atomic_dec(&root->orphan_inodes);
	}

	return 0;
}