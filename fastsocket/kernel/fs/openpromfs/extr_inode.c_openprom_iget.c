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
struct inode {int i_state; scalar_t__ i_ino; int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int I_NEW ; 
 scalar_t__ OPENPROM_ROOT_INO ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 struct inode* iget_locked (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openprom_inode_operations ; 
 int /*<<< orphan*/  openprom_operations ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static struct inode *openprom_iget(struct super_block *sb, ino_t ino)
{
	struct inode *inode;

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (inode->i_state & I_NEW) {
		inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;
		if (inode->i_ino == OPENPROM_ROOT_INO) {
			inode->i_op = &openprom_inode_operations;
			inode->i_fop = &openprom_operations;
			inode->i_mode = S_IFDIR | S_IRUGO | S_IXUGO;
		}
		unlock_new_inode(inode);
	}
	return inode;
}