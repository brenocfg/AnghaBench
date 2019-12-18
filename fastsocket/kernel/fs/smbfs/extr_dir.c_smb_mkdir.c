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
struct TYPE_2__ {int capabilities; } ;
struct smb_sb_info {TYPE_1__ opt; } ;
struct inode {int dummy; } ;
struct iattr {int ia_mode; int /*<<< orphan*/  ia_valid; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 int SMB_CAP_UNIX ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 int smb_instantiate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_invalid_dir_cache (struct inode*) ; 
 int smb_proc_mkdir (struct dentry*) ; 
 int smb_proc_setattr_unix (struct dentry*,struct iattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
smb_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	struct smb_sb_info *server = server_from_dentry(dentry);
	int error;
	struct iattr attr;

	lock_kernel();
	smb_invalid_dir_cache(dir);
	error = smb_proc_mkdir(dentry);
	if (!error) {
		if (server->opt.capabilities & SMB_CAP_UNIX) {
			/* Set attributes for new directory */
			attr.ia_valid = ATTR_MODE;
			attr.ia_mode = mode;
			error = smb_proc_setattr_unix(dentry, &attr, 0, 0);
		}
		error = smb_instantiate(dentry, 0, 0);
	}
	unlock_kernel();
	return error;
}