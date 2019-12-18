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
struct super_block {int dummy; } ;
struct inode {int i_state; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_key {int /*<<< orphan*/  objectid; } ;
struct TYPE_2__ {int /*<<< orphan*/  location; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 int I_NEW ; 
 struct inode* btrfs_iget_locked (struct super_block*,int /*<<< orphan*/ ,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_read_locked_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_tree_add (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *btrfs_iget(struct super_block *s, struct btrfs_key *location,
			 struct btrfs_root *root, int *new)
{
	struct inode *inode;

	inode = btrfs_iget_locked(s, location->objectid, root);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (inode->i_state & I_NEW) {
		BTRFS_I(inode)->root = root;
		memcpy(&BTRFS_I(inode)->location, location, sizeof(*location));
		btrfs_read_locked_inode(inode);
		if (!is_bad_inode(inode)) {
			inode_tree_add(inode);
			unlock_new_inode(inode);
			if (new)
				*new = 1;
		} else {
			unlock_new_inode(inode);
			iput(inode);
			inode = ERR_PTR(-ESTALE);
		}
	}

	return inode;
}