#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct pohmelfs_inode {int /*<<< orphan*/  ino; } ;
struct inode {int /*<<< orphan*/  i_mode; TYPE_2__* i_sb; } ;
struct dentry {struct qstr d_name; struct inode* d_inode; } ;
struct TYPE_4__ {TYPE_1__* s_op; } ;
struct TYPE_3__ {int (* write_inode ) (struct inode*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct pohmelfs_inode* POHMELFS_I (struct inode*) ; 
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pohmelfs_create_entry (struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pohmelfs_create_link (struct pohmelfs_inode*,struct qstr*,struct pohmelfs_inode*,int /*<<< orphan*/ *) ; 
 int stub1 (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pohmelfs_link(struct dentry *old_dentry, struct inode *dir,
	struct dentry *dentry)
{
	struct inode *inode = old_dentry->d_inode;
	struct pohmelfs_inode *pi = POHMELFS_I(inode);
	int err;
	struct qstr str = dentry->d_name;

	str.hash = jhash(dentry->d_name.name, dentry->d_name.len, 0);

	err = inode->i_sb->s_op->write_inode(inode, 0);
	if (err)
		return err;

	err = pohmelfs_create_link(POHMELFS_I(dir), &str, pi, NULL);
	if (err)
		return err;

	return pohmelfs_create_entry(dir, dentry, pi->ino, inode->i_mode);
}