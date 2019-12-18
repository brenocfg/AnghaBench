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
struct smb_sb_info {TYPE_2__* mnt; } ;
struct smb_fattr {int /*<<< orphan*/  f_ino; } ;
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/ * d_op; int /*<<< orphan*/  d_sb; TYPE_1__ d_name; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int EACCES ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  PARANOIA (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SMB_MAXNAMELEN ; 
 int SMB_MOUNT_CASE ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  iunique (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 scalar_t__ memchr (int /*<<< orphan*/ ,char,scalar_t__) ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 struct inode* smb_iget (int /*<<< orphan*/ ,struct smb_fattr*) ; 
 int smb_proc_getattr (struct dentry*,struct smb_fattr*) ; 
 int /*<<< orphan*/  smb_renew_times (struct dentry*) ; 
 int /*<<< orphan*/  smbfs_dentry_operations ; 
 int /*<<< orphan*/  smbfs_dentry_operations_case ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static struct dentry *
smb_lookup(struct inode *dir, struct dentry *dentry, struct nameidata *nd)
{
	struct smb_fattr finfo;
	struct inode *inode;
	int error;
	struct smb_sb_info *server;

	error = -ENAMETOOLONG;
	if (dentry->d_name.len > SMB_MAXNAMELEN)
		goto out;

	/* Do not allow lookup of names with backslashes in */
	error = -EINVAL;
	if (memchr(dentry->d_name.name, '\\', dentry->d_name.len))
		goto out;

	lock_kernel();
	error = smb_proc_getattr(dentry, &finfo);
#ifdef SMBFS_PARANOIA
	if (error && error != -ENOENT)
		PARANOIA("find %s/%s failed, error=%d\n",
			 DENTRY_PATH(dentry), error);
#endif

	inode = NULL;
	if (error == -ENOENT)
		goto add_entry;
	if (!error) {
		error = -EACCES;
		finfo.f_ino = iunique(dentry->d_sb, 2);
		inode = smb_iget(dir->i_sb, &finfo);
		if (inode) {
	add_entry:
			server = server_from_dentry(dentry);
			if (server->mnt->flags & SMB_MOUNT_CASE)
				dentry->d_op = &smbfs_dentry_operations_case;
			else
				dentry->d_op = &smbfs_dentry_operations;

			d_add(dentry, inode);
			smb_renew_times(dentry);
			error = 0;
		}
	}
	unlock_kernel();
out:
	return ERR_PTR(error);
}