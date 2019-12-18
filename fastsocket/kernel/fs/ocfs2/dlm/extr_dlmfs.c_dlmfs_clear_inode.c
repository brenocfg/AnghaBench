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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_ino; } ;
struct dlmfs_inode_private {int /*<<< orphan*/ * ip_dlm; int /*<<< orphan*/ * ip_parent; int /*<<< orphan*/  ip_lockres; } ;

/* Variables and functions */
 struct dlmfs_inode_private* DLMFS_I (struct inode*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int user_dlm_destroy_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_dlm_unregister_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlmfs_clear_inode(struct inode *inode)
{
	int status;
	struct dlmfs_inode_private *ip;

	if (!inode)
		return;

	mlog(0, "inode %lu\n", inode->i_ino);

	ip = DLMFS_I(inode);

	if (S_ISREG(inode->i_mode)) {
		status = user_dlm_destroy_lock(&ip->ip_lockres);
		if (status < 0)
			mlog_errno(status);
		iput(ip->ip_parent);
		goto clear_fields;
	}

	mlog(0, "we're a directory, ip->ip_dlm = 0x%p\n", ip->ip_dlm);
	/* we must be a directory. If required, lets unregister the
	 * dlm context now. */
	if (ip->ip_dlm)
		user_dlm_unregister_context(ip->ip_dlm);
clear_fields:
	ip->ip_parent = NULL;
	ip->ip_dlm = NULL;
}