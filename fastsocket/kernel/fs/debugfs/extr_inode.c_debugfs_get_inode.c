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
struct inode {int i_mode; void* i_private; struct file_operations const* i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;
struct file_operations {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
#define  S_IFDIR 130 
#define  S_IFLNK 129 
 int S_IFMT ; 
#define  S_IFREG 128 
 struct file_operations const debugfs_file_operations ; 
 int /*<<< orphan*/  debugfs_link_operations ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 struct file_operations const simple_dir_operations ; 

__attribute__((used)) static struct inode *debugfs_get_inode(struct super_block *sb, int mode, dev_t dev,
				       void *data, const struct file_operations *fops)

{
	struct inode *inode = new_inode(sb);

	if (inode) {
		inode->i_mode = mode;
		inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
		switch (mode & S_IFMT) {
		default:
			init_special_inode(inode, mode, dev);
			break;
		case S_IFREG:
			inode->i_fop = fops ? fops : &debugfs_file_operations;
			inode->i_private = data;
			break;
		case S_IFLNK:
			inode->i_op = &debugfs_link_operations;
			inode->i_fop = fops;
			inode->i_private = data;
			break;
		case S_IFDIR:
			inode->i_op = &simple_dir_inode_operations;
			inode->i_fop = fops ? fops : &simple_dir_operations;
			inode->i_private = data;

			/* directory inodes start off with i_nlink == 2
			 * (for "." entry) */
			inc_nlink(inode);
			break;
		}
	}
	return inode; 
}