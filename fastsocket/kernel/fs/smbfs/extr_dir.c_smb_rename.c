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
struct inode {int dummy; } ;
struct dentry {scalar_t__ d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  smb_close (scalar_t__) ; 
 int /*<<< orphan*/  smb_invalid_dir_cache (struct inode*) ; 
 int smb_proc_mv (struct dentry*,struct dentry*) ; 
 int smb_proc_unlink (struct dentry*) ; 
 int /*<<< orphan*/  smb_renew_times (struct dentry*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
smb_rename(struct inode *old_dir, struct dentry *old_dentry,
	   struct inode *new_dir, struct dentry *new_dentry)
{
	int error;

	/*
	 * Close any open files, and check whether to delete the
	 * target before attempting the rename.
	 */
	lock_kernel();
	if (old_dentry->d_inode)
		smb_close(old_dentry->d_inode);
	if (new_dentry->d_inode) {
		smb_close(new_dentry->d_inode);
		error = smb_proc_unlink(new_dentry);
		if (error) {
			VERBOSE("unlink %s/%s, error=%d\n",
				DENTRY_PATH(new_dentry), error);
			goto out;
		}
		/* FIXME */
		d_delete(new_dentry);
	}

	smb_invalid_dir_cache(old_dir);
	smb_invalid_dir_cache(new_dir);
	error = smb_proc_mv(old_dentry, new_dentry);
	if (!error) {
		smb_renew_times(old_dentry);
		smb_renew_times(new_dentry);
	}
out:
	unlock_kernel();
	return error;
}