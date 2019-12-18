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
typedef  scalar_t__ time_t ;
struct smb_inode_info {int /*<<< orphan*/  oldmtime; int /*<<< orphan*/  attr; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct smb_fattr {scalar_t__ f_size; int /*<<< orphan*/  attr; int /*<<< orphan*/  f_atime; TYPE_1__ f_mtime; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_ctime; int /*<<< orphan*/  f_gid; int /*<<< orphan*/  f_uid; int /*<<< orphan*/  f_nlink; int /*<<< orphan*/  f_mode; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mode; TYPE_1__ i_mtime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_nlink; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct smb_inode_info* SMB_I (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERBOSE (char*,int /*<<< orphan*/ ,long,long,long,long) ; 
 int /*<<< orphan*/  invalidate_remote_inode (struct inode*) ; 
 int /*<<< orphan*/  jiffies ; 

void
smb_set_inode_attr(struct inode *inode, struct smb_fattr *fattr)
{
	struct smb_inode_info *ei = SMB_I(inode);

	/*
	 * A size change should have a different mtime, or same mtime
	 * but different size.
	 */
	time_t last_time = inode->i_mtime.tv_sec;
	loff_t last_sz = inode->i_size;

	inode->i_mode	= fattr->f_mode;
	inode->i_nlink	= fattr->f_nlink;
	inode->i_uid	= fattr->f_uid;
	inode->i_gid	= fattr->f_gid;
	inode->i_ctime	= fattr->f_ctime;
	inode->i_blocks = fattr->f_blocks;
	inode->i_size	= fattr->f_size;
	inode->i_mtime	= fattr->f_mtime;
	inode->i_atime	= fattr->f_atime;
	ei->attr = fattr->attr;

	/*
	 * Update the "last time refreshed" field for revalidation.
	 */
	ei->oldmtime = jiffies;

	if (inode->i_mtime.tv_sec != last_time || inode->i_size != last_sz) {
		VERBOSE("%ld changed, old=%ld, new=%ld, oz=%ld, nz=%ld\n",
			inode->i_ino,
			(long) last_time, (long) inode->i_mtime.tv_sec,
			(long) last_sz, (long) inode->i_size);

		if (!S_ISDIR(inode->i_mode))
			invalidate_remote_inode(inode);
	}
}