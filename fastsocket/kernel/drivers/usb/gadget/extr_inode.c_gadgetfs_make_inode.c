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
struct inode {int i_mode; struct file_operations const* i_fop; void* i_private; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct file_operations {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  default_gid ; 
 int /*<<< orphan*/  default_uid ; 
 struct inode* new_inode (struct super_block*) ; 

__attribute__((used)) static struct inode *
gadgetfs_make_inode (struct super_block *sb,
		void *data, const struct file_operations *fops,
		int mode)
{
	struct inode *inode = new_inode (sb);

	if (inode) {
		inode->i_mode = mode;
		inode->i_uid = default_uid;
		inode->i_gid = default_gid;
		inode->i_atime = inode->i_mtime = inode->i_ctime
				= CURRENT_TIME;
		inode->i_private = data;
		inode->i_fop = fops;
	}
	return inode;
}