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
struct smb_sb_info {TYPE_1__* mnt; } ;
struct dentry {int /*<<< orphan*/  d_time; int /*<<< orphan*/ * d_op; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int SMB_MOUNT_CASE ; 
 int /*<<< orphan*/  jiffies ; 
 struct smb_sb_info* server_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  smbfs_dentry_operations ; 
 int /*<<< orphan*/  smbfs_dentry_operations_case ; 

void
smb_new_dentry(struct dentry *dentry)
{
	struct smb_sb_info *server = server_from_dentry(dentry);

	if (server->mnt->flags & SMB_MOUNT_CASE)
		dentry->d_op = &smbfs_dentry_operations_case;
	else
		dentry->d_op = &smbfs_dentry_operations;
	dentry->d_time = jiffies;
}