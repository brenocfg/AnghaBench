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
 int /*<<< orphan*/  DEBUG1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int /*<<< orphan*/  server_from_dentry (struct dentry*) ; 
 int smb_instantiate (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_invalid_dir_cache (struct inode*) ; 
 int smb_proc_link (int /*<<< orphan*/ ,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  smb_renew_times (struct dentry*) ; 

__attribute__((used)) static int
smb_link(struct dentry *dentry, struct inode *dir, struct dentry *new_dentry)
{
	int error;

	DEBUG1("smb_link old=%s/%s new=%s/%s\n",
	       DENTRY_PATH(dentry), DENTRY_PATH(new_dentry));
	smb_invalid_dir_cache(dir);
	error = smb_proc_link(server_from_dentry(dentry), dentry, new_dentry);
	if (!error) {
		smb_renew_times(dentry);
		error = smb_instantiate(new_dentry, 0, 0);
	}
	return error;
}