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
struct smb_fattr {int f_mode; int /*<<< orphan*/  attr; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_atime; int /*<<< orphan*/  f_ctime; int /*<<< orphan*/  f_mtime; int /*<<< orphan*/  f_size; int /*<<< orphan*/  f_gid; int /*<<< orphan*/  f_uid; int /*<<< orphan*/  f_ino; int /*<<< orphan*/  f_nlink; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_nlink; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 TYPE_1__* SMB_I (struct inode*) ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  aRONLY ; 
 int /*<<< orphan*/  memset (struct smb_fattr*,int /*<<< orphan*/ ,int) ; 

void
smb_get_inode_attr(struct inode *inode, struct smb_fattr *fattr)
{
	memset(fattr, 0, sizeof(struct smb_fattr));
	fattr->f_mode	= inode->i_mode;
	fattr->f_nlink	= inode->i_nlink;
	fattr->f_ino	= inode->i_ino;
	fattr->f_uid	= inode->i_uid;
	fattr->f_gid	= inode->i_gid;
	fattr->f_size	= inode->i_size;
	fattr->f_mtime	= inode->i_mtime;
	fattr->f_ctime	= inode->i_ctime;
	fattr->f_atime	= inode->i_atime;
	fattr->f_blocks	= inode->i_blocks;

	fattr->attr	= SMB_I(inode)->attr;
	/*
	 * Keep the attributes in sync with the inode permissions.
	 */
	if (fattr->f_mode & S_IWUSR)
		fattr->attr &= ~aRONLY;
	else
		fattr->attr |= aRONLY;
}