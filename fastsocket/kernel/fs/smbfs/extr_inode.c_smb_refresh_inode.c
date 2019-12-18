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
struct smb_fattr {int f_mode; } ;
struct inode {int i_ino; int i_mode; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int EIO ; 
 int /*<<< orphan*/  PARANOIA (char*,int /*<<< orphan*/ ,int,int) ; 
 int S_IFMT ; 
 int /*<<< orphan*/  S_ISDIR (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 int /*<<< orphan*/  invalidate_remote_inode (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  smb_invalid_dir_cache (struct inode*) ; 
 int smb_proc_getattr (struct dentry*,struct smb_fattr*) ; 
 int /*<<< orphan*/  smb_renew_times (struct dentry*) ; 
 int /*<<< orphan*/  smb_set_inode_attr (struct inode*,struct smb_fattr*) ; 

__attribute__((used)) static int
smb_refresh_inode(struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	int error;
	struct smb_fattr fattr;

	error = smb_proc_getattr(dentry, &fattr);
	if (!error) {
		smb_renew_times(dentry);
		/*
		 * Check whether the type part of the mode changed,
		 * and don't update the attributes if it did.
		 *
		 * And don't dick with the root inode
		 */
		if (inode->i_ino == 2)
			return error;
		if (S_ISLNK(inode->i_mode))
			return error;	/* VFS will deal with it */

		if ((inode->i_mode & S_IFMT) == (fattr.f_mode & S_IFMT)) {
			smb_set_inode_attr(inode, &fattr);
		} else {
			/*
			 * Big trouble! The inode has become a new object,
			 * so any operations attempted on it are invalid.
			 *
			 * To limit damage, mark the inode as bad so that
			 * subsequent lookup validations will fail.
			 */
			PARANOIA("%s/%s changed mode, %07o to %07o\n",
				 DENTRY_PATH(dentry),
				 inode->i_mode, fattr.f_mode);

			fattr.f_mode = inode->i_mode; /* save mode */
			make_bad_inode(inode);
			inode->i_mode = fattr.f_mode; /* restore mode */
			/*
			 * No need to worry about unhashing the dentry: the
			 * lookup validation will see that the inode is bad.
			 * But we do want to invalidate the caches ...
			 */
			if (!S_ISDIR(inode->i_mode))
				invalidate_remote_inode(inode);
			else
				smb_invalid_dir_cache(inode);
			error = -EIO;
		}
	}
	return error;
}