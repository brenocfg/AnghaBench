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
struct smb_sb_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {scalar_t__ oldmtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 (char*) ; 
 TYPE_1__* SMB_I (struct inode*) ; 
 scalar_t__ SMB_MAX_AGE (struct smb_sb_info*) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 int smb_refresh_inode (struct dentry*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

int
smb_revalidate_inode(struct dentry *dentry)
{
	struct smb_sb_info *s = server_from_dentry(dentry);
	struct inode *inode = dentry->d_inode;
	int error = 0;

	DEBUG1("smb_revalidate_inode\n");
	lock_kernel();

	/*
	 * Check whether we've recently refreshed the inode.
	 */
	if (time_before(jiffies, SMB_I(inode)->oldmtime + SMB_MAX_AGE(s))) {
		VERBOSE("up-to-date, ino=%ld, jiffies=%lu, oldtime=%lu\n",
			inode->i_ino, jiffies, SMB_I(inode)->oldmtime);
		goto out;
	}

	error = smb_refresh_inode(dentry);
out:
	unlock_kernel();
	return error;
}