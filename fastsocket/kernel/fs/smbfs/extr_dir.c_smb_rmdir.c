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
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  smb_close (struct inode*) ; 
 int /*<<< orphan*/  smb_invalid_dir_cache (struct inode*) ; 
 int smb_proc_rmdir (struct dentry*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
smb_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	int error;

	/*
	 * Close the directory if it's open.
	 */
	lock_kernel();
	smb_close(inode);

	/*
	 * Check that nobody else is using the directory..
	 */
	error = -EBUSY;
	if (!d_unhashed(dentry))
		goto out;

	smb_invalid_dir_cache(dir);
	error = smb_proc_rmdir(dentry);

out:
	unlock_kernel();
	return error;
}