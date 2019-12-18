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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  server_from_dentry (struct dentry*) ; 
 int smb_proc_symlink (int /*<<< orphan*/ ,struct dentry*,char const*) ; 

int smb_symlink(struct inode *inode, struct dentry *dentry, const char *oldname)
{
	DEBUG1("create symlink %s -> %s/%s\n", oldname, DENTRY_PATH(dentry));

	return smb_proc_symlink(server_from_dentry(dentry), dentry, oldname);
}