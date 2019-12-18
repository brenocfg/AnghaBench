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
struct super_block {TYPE_2__* s_root; } ;
struct inode {int i_nlink; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_size; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;
struct autofs_info {int /*<<< orphan*/  size; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {TYPE_1__* d_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autofs4_dir_inode_operations ; 
 int /*<<< orphan*/  autofs4_dir_operations ; 
 int /*<<< orphan*/  autofs4_symlink_inode_operations ; 
 struct inode* new_inode (struct super_block*) ; 

struct inode *autofs4_get_inode(struct super_block *sb,
				struct autofs_info *inf)
{
	struct inode *inode = new_inode(sb);

	if (inode == NULL)
		return NULL;

	inode->i_mode = inf->mode;
	if (sb->s_root) {
		inode->i_uid = sb->s_root->d_inode->i_uid;
		inode->i_gid = sb->s_root->d_inode->i_gid;
	}
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;

	if (S_ISDIR(inf->mode)) {
		inode->i_nlink = 2;
		inode->i_op = &autofs4_dir_inode_operations;
		inode->i_fop = &autofs4_dir_operations;
	} else if (S_ISLNK(inf->mode)) {
		inode->i_size = inf->size;
		inode->i_op = &autofs4_symlink_inode_operations;
	}

	return inode;
}