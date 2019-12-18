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
struct inode {int i_mode; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_fs_time (int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 

__attribute__((used)) static struct inode *bm_get_inode(struct super_block *sb, int mode)
{
	struct inode * inode = new_inode(sb);

	if (inode) {
		inode->i_mode = mode;
		inode->i_atime = inode->i_mtime = inode->i_ctime =
			current_fs_time(inode->i_sb);
	}
	return inode;
}