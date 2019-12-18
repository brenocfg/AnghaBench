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
struct btrfs_root {int /*<<< orphan*/  root_item; } ;
struct TYPE_2__ {struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  btrfs_is_free_space_inode (struct btrfs_root*,struct inode*) ; 
 scalar_t__ btrfs_root_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  generic_drop_inode (struct inode*) ; 

void btrfs_drop_inode(struct inode *inode)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;

	if (btrfs_root_refs(&root->root_item) == 0 &&
	    !btrfs_is_free_space_inode(root, inode))
		generic_delete_inode(inode);
	else
		generic_drop_inode(inode);
}