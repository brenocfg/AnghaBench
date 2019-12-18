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
struct inode {int i_nlink; int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

__attribute__((used)) static struct inode *ocfs2_get_init_inode(struct inode *dir, int mode)
{
	struct inode *inode;

	inode = new_inode(dir->i_sb);
	if (!inode) {
		mlog(ML_ERROR, "new_inode failed!\n");
		return NULL;
	}

	/* populate as many fields early on as possible - many of
	 * these are used by the support functions here and in
	 * callers. */
	if (S_ISDIR(mode))
		inode->i_nlink = 2;
	else
		inode->i_nlink = 1;
	inode->i_uid = current_fsuid();
	if (dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode))
			mode |= S_ISGID;
	} else
		inode->i_gid = current_fsgid();
	inode->i_mode = mode;
	vfs_dq_init(inode);
	return inode;
}