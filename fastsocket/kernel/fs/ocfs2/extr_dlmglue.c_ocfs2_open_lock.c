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
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {struct ocfs2_lock_res ip_open_lockres; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_LOCK_PR ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_cluster_lock (struct ocfs2_super*,struct ocfs2_lock_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_mount_local (struct ocfs2_super*) ; 

int ocfs2_open_lock(struct inode *inode)
{
	int status = 0;
	struct ocfs2_lock_res *lockres;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	BUG_ON(!inode);

	mlog_entry_void();

	mlog(0, "inode %llu take PRMODE open lock\n",
	     (unsigned long long)OCFS2_I(inode)->ip_blkno);

	if (ocfs2_mount_local(osb))
		goto out;

	lockres = &OCFS2_I(inode)->ip_open_lockres;

	status = ocfs2_cluster_lock(OCFS2_SB(inode->i_sb), lockres,
				    DLM_LOCK_PR, 0, 0);
	if (status < 0)
		mlog_errno(status);

out:
	mlog_exit(status);
	return status;
}