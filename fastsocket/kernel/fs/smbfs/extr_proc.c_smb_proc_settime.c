#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ protocol; } ;
struct smb_sb_info {TYPE_2__* mnt; TYPE_1__ opt; } ;
struct smb_fattr {int /*<<< orphan*/  f_mtime; } ;
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_6__ {scalar_t__ access; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int EACCES ; 
 TYPE_3__* SMB_I (struct inode*) ; 
 int SMB_MOUNT_WIN95 ; 
 scalar_t__ SMB_O_RDONLY ; 
 scalar_t__ SMB_PROTOCOL_LANMAN2 ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 scalar_t__ smb_is_open (struct inode*) ; 
 int smb_proc_close_inode (struct smb_sb_info*,struct inode*) ; 
 int /*<<< orphan*/  smb_proc_open (struct smb_sb_info*,struct dentry*,scalar_t__) ; 
 int smb_proc_setattr_ext (struct smb_sb_info*,struct inode*,struct smb_fattr*) ; 
 int smb_proc_setattr_trans2 (struct smb_sb_info*,struct dentry*,struct smb_fattr*) ; 

int
smb_proc_settime(struct dentry *dentry, struct smb_fattr *fattr)
{
	struct smb_sb_info *server = server_from_dentry(dentry);
	struct inode *inode = dentry->d_inode;
	int result;

	VERBOSE("setting %s/%s, open=%d\n",
		DENTRY_PATH(dentry), smb_is_open(inode));

	/* setting the time on a Win95 server fails (tridge) */
	if (server->opt.protocol >= SMB_PROTOCOL_LANMAN2 && 
	    !(server->mnt->flags & SMB_MOUNT_WIN95)) {
		if (smb_is_open(inode) && SMB_I(inode)->access != SMB_O_RDONLY)
			result = smb_proc_setattr_ext(server, inode, fattr);
		else
			result = smb_proc_setattr_trans2(server, dentry, fattr);
	} else {
		/*
		 * Fail silently on directories ... timestamp can't be set?
		 */
		result = 0;
		if (S_ISREG(inode->i_mode)) {
			/*
			 * Set the mtime by opening and closing the file.
			 * Note that the file is opened read-only, but this
			 * still allows us to set the date (tridge)
			 */
			result = -EACCES;
			if (!smb_is_open(inode))
				smb_proc_open(server, dentry, SMB_O_RDONLY);
			if (smb_is_open(inode)) {
				inode->i_mtime = fattr->f_mtime;
				result = smb_proc_close_inode(server, inode);
			}
		}
	}

	return result;
}