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
struct smb_sb_info {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {unsigned long d_time; struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  PARANOIA (char*,int /*<<< orphan*/ ) ; 
 unsigned long SMB_MAX_AGE (struct smb_sb_info*) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 scalar_t__ smb_revalidate_inode (struct dentry*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
smb_lookup_validate(struct dentry * dentry, struct nameidata *nd)
{
	struct smb_sb_info *server = server_from_dentry(dentry);
	struct inode * inode = dentry->d_inode;
	unsigned long age = jiffies - dentry->d_time;
	int valid;

	/*
	 * The default validation is based on dentry age:
	 * we believe in dentries for a few seconds.  (But each
	 * successful server lookup renews the timestamp.)
	 */
	valid = (age <= SMB_MAX_AGE(server));
#ifdef SMBFS_DEBUG_VERBOSE
	if (!valid)
		VERBOSE("%s/%s not valid, age=%lu\n", 
			DENTRY_PATH(dentry), age);
#endif

	if (inode) {
		lock_kernel();
		if (is_bad_inode(inode)) {
			PARANOIA("%s/%s has dud inode\n", DENTRY_PATH(dentry));
			valid = 0;
		} else if (!valid)
			valid = (smb_revalidate_inode(dentry) == 0);
		unlock_kernel();
	} else {
		/*
		 * What should we do for negative dentries?
		 */
	}
	return valid;
}