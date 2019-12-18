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
struct inode {int i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ino; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_key {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  location; struct btrfs_root* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_EMPTY_SUBVOL_DIR_OBJECTID ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_DUMMY ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  btrfs_dir_ro_inode_operations ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct btrfs_key*,int) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static struct inode *new_simple_dir(struct super_block *s,
				    struct btrfs_key *key,
				    struct btrfs_root *root)
{
	struct inode *inode = new_inode(s);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	BTRFS_I(inode)->root = root;
	memcpy(&BTRFS_I(inode)->location, key, sizeof(*key));
	set_bit(BTRFS_INODE_DUMMY, &BTRFS_I(inode)->runtime_flags);

	inode->i_ino = BTRFS_EMPTY_SUBVOL_DIR_OBJECTID;
	inode->i_op = &btrfs_dir_ro_inode_operations;
	inode->i_fop = &simple_dir_operations;
	inode->i_mode = S_IFDIR | S_IRUGO | S_IWUSR | S_IXUGO;
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;

	return inode;
}