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
struct smb_fattr {int /*<<< orphan*/  attr; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  smb_is_open (int /*<<< orphan*/ ) ; 
 int smb_proc_setattr_core (struct smb_sb_info*,struct dentry*,int /*<<< orphan*/ ) ; 

int
smb_proc_setattr(struct dentry *dir, struct smb_fattr *fattr)
{
	struct smb_sb_info *server = server_from_dentry(dir);
	int result;

	VERBOSE("setting %s/%s, open=%d\n", 
		DENTRY_PATH(dir), smb_is_open(dir->d_inode));
	result = smb_proc_setattr_core(server, dir, fattr->attr);
	return result;
}