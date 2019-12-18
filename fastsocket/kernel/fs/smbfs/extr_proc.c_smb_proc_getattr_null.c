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
struct smb_sb_info {TYPE_1__* ops; } ;
struct smb_fattr {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* getattr ) (struct smb_sb_info*,struct dentry*,struct smb_fattr*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  smb_finish_dirent (struct smb_sb_info*,struct smb_fattr*) ; 
 int /*<<< orphan*/  smb_init_dirent (struct smb_sb_info*,struct smb_fattr*) ; 
 scalar_t__ smb_proc_ops_wait (struct smb_sb_info*) ; 
 int stub1 (struct smb_sb_info*,struct dentry*,struct smb_fattr*) ; 

__attribute__((used)) static int
smb_proc_getattr_null(struct smb_sb_info *server, struct dentry *dir,
			  struct smb_fattr *fattr)
{
	int result;

	if (smb_proc_ops_wait(server) < 0)
		return -EIO;

	smb_init_dirent(server, fattr);
	result = server->ops->getattr(server, dir, fattr);
	smb_finish_dirent(server, fattr);

	return result;
}