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
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  smb_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_invalid_dir_cache (struct inode*) ; 
 int smb_proc_unlink (struct dentry*) ; 
 int /*<<< orphan*/  smb_renew_times (struct dentry*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
smb_unlink(struct inode *dir, struct dentry *dentry)
{
	int error;

	/*
	 * Close the file if it's open.
	 */
	lock_kernel();
	smb_close(dentry->d_inode);

	smb_invalid_dir_cache(dir);
	error = smb_proc_unlink(dentry);
	if (!error)
		smb_renew_times(dentry);
	unlock_kernel();
	return error;
}