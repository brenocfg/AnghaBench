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
struct nameidata {int dummy; } ;
struct inode {int dummy; } ;
struct iattr {int ia_mode; int /*<<< orphan*/  ia_valid; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  PARANOIA (char*,int /*<<< orphan*/ ,int) ; 
 int SMB_CAP_UNIX ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  lock_kernel () ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 int smb_instantiate (struct dentry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smb_invalid_dir_cache (struct inode*) ; 
 int smb_proc_create (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smb_proc_setattr_unix (struct dentry*,struct iattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
smb_create(struct inode *dir, struct dentry *dentry, int mode,
		struct nameidata *nd)
{
	struct smb_sb_info *server = server_from_dentry(dentry);
	__u16 fileid;
	int error;
	struct iattr attr;

	VERBOSE("creating %s/%s, mode=%d\n", DENTRY_PATH(dentry), mode);

	lock_kernel();
	smb_invalid_dir_cache(dir);
	error = smb_proc_create(dentry, 0, get_seconds(), &fileid);
	if (!error) {
		if (server->opt.capabilities & SMB_CAP_UNIX) {
			/* Set attributes for new file */
			attr.ia_valid = ATTR_MODE;
			attr.ia_mode = mode;
			error = smb_proc_setattr_unix(dentry, &attr, 0, 0);
		}
		error = smb_instantiate(dentry, fileid, 1);
	} else {
		PARANOIA("%s/%s failed, error=%d\n",
			 DENTRY_PATH(dentry), error);
	}
	unlock_kernel();
	return error;
}