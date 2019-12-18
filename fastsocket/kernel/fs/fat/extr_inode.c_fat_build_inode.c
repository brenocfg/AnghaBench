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
struct super_block {int dummy; } ;
struct msdos_dir_entry {int dummy; } ;
struct inode {int i_version; int /*<<< orphan*/  i_ino; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  MSDOS_ROOT_INO ; 
 int /*<<< orphan*/  fat_attach (struct inode*,int /*<<< orphan*/ ) ; 
 int fat_fill_inode (struct inode*,struct msdos_dir_entry*) ; 
 struct inode* fat_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  iunique (struct super_block*,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 

struct inode *fat_build_inode(struct super_block *sb,
			struct msdos_dir_entry *de, loff_t i_pos)
{
	struct inode *inode;
	int err;

	inode = fat_iget(sb, i_pos);
	if (inode)
		goto out;
	inode = new_inode(sb);
	if (!inode) {
		inode = ERR_PTR(-ENOMEM);
		goto out;
	}
	inode->i_ino = iunique(sb, MSDOS_ROOT_INO);
	inode->i_version = 1;
	err = fat_fill_inode(inode, de);
	if (err) {
		iput(inode);
		inode = ERR_PTR(err);
		goto out;
	}
	fat_attach(inode, i_pos);
	insert_inode_hash(inode);
out:
	return inode;
}