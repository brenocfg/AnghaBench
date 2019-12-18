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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int dummy; } ;
struct autofs_info {int flags; int /*<<< orphan*/  last_used; } ;

/* Variables and functions */
 int AUTOFS_INF_PENDING ; 
 int /*<<< orphan*/  DPRINTK (char*,int,...) ; 
 int /*<<< orphan*/  NFY_MOUNT ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int autofs4_wait (struct autofs_sb_info*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static int autofs4_mount_wait(struct dentry *dentry)
{
	struct autofs_sb_info *sbi = autofs4_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	int status = 0;

	if (ino->flags & AUTOFS_INF_PENDING) {
		DPRINTK("waiting for mount name=%.*s",
			dentry->d_name.len, dentry->d_name.name);
		status = autofs4_wait(sbi, dentry, NFY_MOUNT);
		DPRINTK("mount wait done status=%d", status);
	}
	ino->last_used = jiffies;
	return status;
}