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
struct timespec {int dummy; } ;
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;
struct inode {int i_state; int i_size; int i_blocks; int /*<<< orphan*/  i_mode; TYPE_1__ i_data; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; struct timespec i_ctime; struct timespec i_atime; struct timespec i_mtime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct cramfs_inode {int size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRAMINO (struct cramfs_inode*) ; 
 int I_NEW ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cramfs_aops ; 
 int /*<<< orphan*/  cramfs_dir_inode_operations ; 
 int /*<<< orphan*/  cramfs_directory_operations ; 
 int /*<<< orphan*/  cramfs_iget5_set ; 
 int /*<<< orphan*/  cramfs_iget5_test ; 
 int /*<<< orphan*/  generic_ro_fops ; 
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cramfs_inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_decode_dev (int) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static struct inode *get_cramfs_inode(struct super_block *sb,
				struct cramfs_inode * cramfs_inode)
{
	struct inode *inode = iget5_locked(sb, CRAMINO(cramfs_inode),
					    cramfs_iget5_test, cramfs_iget5_set,
					    cramfs_inode);
	static struct timespec zerotime;

	if (inode && (inode->i_state & I_NEW)) {
		inode->i_mode = cramfs_inode->mode;
		inode->i_uid = cramfs_inode->uid;
		inode->i_size = cramfs_inode->size;
		inode->i_blocks = (cramfs_inode->size - 1) / 512 + 1;
		inode->i_gid = cramfs_inode->gid;
		/* Struct copy intentional */
		inode->i_mtime = inode->i_atime = inode->i_ctime = zerotime;
		/* inode->i_nlink is left 1 - arguably wrong for directories,
		   but it's the best we can do without reading the directory
		   contents.  1 yields the right result in GNU find, even
		   without -noleaf option. */
		if (S_ISREG(inode->i_mode)) {
			inode->i_fop = &generic_ro_fops;
			inode->i_data.a_ops = &cramfs_aops;
		} else if (S_ISDIR(inode->i_mode)) {
			inode->i_op = &cramfs_dir_inode_operations;
			inode->i_fop = &cramfs_directory_operations;
		} else if (S_ISLNK(inode->i_mode)) {
			inode->i_op = &page_symlink_inode_operations;
			inode->i_data.a_ops = &cramfs_aops;
		} else {
			init_special_inode(inode, inode->i_mode,
				old_decode_dev(cramfs_inode->size));
		}
		unlock_new_inode(inode);
	}
	return inode;
}