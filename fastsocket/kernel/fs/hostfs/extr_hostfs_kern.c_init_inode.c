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
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MKDEV (int,int) ; 
#define  OS_TYPE_BLOCKDEV 131 
#define  OS_TYPE_CHARDEV 130 
 int OS_TYPE_DIR ; 
#define  OS_TYPE_FIFO 129 
#define  OS_TYPE_SOCK 128 
 int OS_TYPE_SYMLINK ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  S_IFIFO ; 
 int /*<<< orphan*/  S_IFSOCK ; 
 char* dentry_name (struct dentry*,int /*<<< orphan*/ ) ; 
 int file_type (char*,int*,int*) ; 
 int /*<<< orphan*/  hostfs_aops ; 
 int /*<<< orphan*/  hostfs_dir_fops ; 
 int /*<<< orphan*/  hostfs_dir_iops ; 
 int /*<<< orphan*/  hostfs_file_fops ; 
 int /*<<< orphan*/  hostfs_iops ; 
 int /*<<< orphan*/  hostfs_link_aops ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 

__attribute__((used)) static int init_inode(struct inode *inode, struct dentry *dentry)
{
	char *name;
	int type, err = -ENOMEM;
	int maj, min;
	dev_t rdev = 0;

	if (dentry) {
		name = dentry_name(dentry, 0);
		if (name == NULL)
			goto out;
		type = file_type(name, &maj, &min);
		/* Reencode maj and min with the kernel encoding.*/
		rdev = MKDEV(maj, min);
		kfree(name);
	}
	else type = OS_TYPE_DIR;

	err = 0;
	if (type == OS_TYPE_SYMLINK)
		inode->i_op = &page_symlink_inode_operations;
	else if (type == OS_TYPE_DIR)
		inode->i_op = &hostfs_dir_iops;
	else inode->i_op = &hostfs_iops;

	if (type == OS_TYPE_DIR) inode->i_fop = &hostfs_dir_fops;
	else inode->i_fop = &hostfs_file_fops;

	if (type == OS_TYPE_SYMLINK)
		inode->i_mapping->a_ops = &hostfs_link_aops;
	else inode->i_mapping->a_ops = &hostfs_aops;

	switch (type) {
	case OS_TYPE_CHARDEV:
		init_special_inode(inode, S_IFCHR, rdev);
		break;
	case OS_TYPE_BLOCKDEV:
		init_special_inode(inode, S_IFBLK, rdev);
		break;
	case OS_TYPE_FIFO:
		init_special_inode(inode, S_IFIFO, 0);
		break;
	case OS_TYPE_SOCK:
		init_special_inode(inode, S_IFSOCK, 0);
		break;
	}
 out:
	return err;
}