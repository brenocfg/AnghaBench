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
struct smb_sb_info {TYPE_2__* ops; } ;
struct smb_cache_control {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_4__ {int (* readdir ) (struct file*,void*,int /*<<< orphan*/ ,struct smb_cache_control*) ;} ;

/* Variables and functions */
 int EIO ; 
 struct smb_sb_info* server_from_dentry (int /*<<< orphan*/ ) ; 
 scalar_t__ smb_proc_ops_wait (struct smb_sb_info*) ; 
 int stub1 (struct file*,void*,int /*<<< orphan*/ ,struct smb_cache_control*) ; 

__attribute__((used)) static int
smb_proc_readdir_null(struct file *filp, void *dirent, filldir_t filldir,
		      struct smb_cache_control *ctl)
{
	struct smb_sb_info *server = server_from_dentry(filp->f_path.dentry);

	if (smb_proc_ops_wait(server) < 0)
		return -EIO;

	return server->ops->readdir(filp, dirent, filldir, ctl);
}