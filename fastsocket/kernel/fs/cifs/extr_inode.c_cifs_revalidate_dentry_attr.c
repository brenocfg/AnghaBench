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
struct super_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  counter; } ;
struct inode {TYPE_1__ i_count; } ;
struct dentry {int /*<<< orphan*/  d_time; struct super_block* d_sb; struct inode* d_inode; } ;
struct TYPE_4__ {scalar_t__ unix_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_SB (struct super_block*) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cFYI (int,char*,char*,struct inode*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cifs_get_inode_info (struct inode**,char*,int /*<<< orphan*/ *,struct super_block*,int,int /*<<< orphan*/ *) ; 
 int cifs_get_inode_info_unix (struct inode**,char*,struct super_block*,int) ; 
 int /*<<< orphan*/  cifs_inode_needs_reval (struct inode*) ; 
 TYPE_2__* cifs_sb_master_tcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (char*) ; 

int cifs_revalidate_dentry_attr(struct dentry *dentry)
{
	int xid;
	int rc = 0;
	struct inode *inode = dentry->d_inode;
	struct super_block *sb = dentry->d_sb;
	char *full_path = NULL;

	if (inode == NULL)
		return -ENOENT;

	if (!cifs_inode_needs_reval(inode))
		return rc;

	xid = GetXid();

	/* can not safely grab the rename sem here if rename calls revalidate
	   since that would deadlock */
	full_path = build_path_from_dentry(dentry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto out;
	}

	cFYI(1, "Update attributes: %s inode 0x%p count %d dentry: 0x%p d_time "
		 "%ld jiffies %ld", full_path, inode, inode->i_count.counter,
		 dentry, dentry->d_time, jiffies);

	if (cifs_sb_master_tcon(CIFS_SB(sb))->unix_ext)
		rc = cifs_get_inode_info_unix(&inode, full_path, sb, xid);
	else
		rc = cifs_get_inode_info(&inode, full_path, NULL, sb,
					 xid, NULL);

out:
	kfree(full_path);
	FreeXid(xid);
	return rc;
}