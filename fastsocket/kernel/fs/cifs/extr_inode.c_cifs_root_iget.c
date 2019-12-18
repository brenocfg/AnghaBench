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
struct super_block {int dummy; } ;
struct inode {int i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_mode; } ;
struct cifs_tcon {scalar_t__ ipc; int /*<<< orphan*/  resource_id; scalar_t__ unix_ext; } ;
struct cifs_sb_info {int /*<<< orphan*/  mnt_gid; int /*<<< orphan*/  mnt_uid; } ;
struct TYPE_2__ {int /*<<< orphan*/  uniqueid; } ;

/* Variables and functions */
 TYPE_1__* CIFS_I (struct inode*) ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 long ENOMEM ; 
 struct inode* ERR_PTR (long) ; 
 int GetXid () ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  _FreeXid (int) ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 char* cifs_build_path_to_root (struct cifs_sb_info*,struct cifs_tcon*) ; 
 long cifs_get_inode_info (struct inode**,char*,int /*<<< orphan*/ *,struct super_block*,int,int /*<<< orphan*/ *) ; 
 long cifs_get_inode_info_unix (struct inode**,char*,struct super_block*,int) ; 
 int /*<<< orphan*/  cifs_ipc_inode_ops ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  simple_dir_operations ; 

struct inode *cifs_root_iget(struct super_block *sb)
{
	int xid;
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	struct inode *inode = NULL;
	long rc;
	char *full_path;
	struct cifs_tcon *tcon = cifs_sb_master_tcon(cifs_sb);

	full_path = cifs_build_path_to_root(cifs_sb, tcon);
	if (full_path == NULL)
		return ERR_PTR(-ENOMEM);

	xid = GetXid();
	if (tcon->unix_ext)
		rc = cifs_get_inode_info_unix(&inode, full_path, sb, xid);
	else
		rc = cifs_get_inode_info(&inode, full_path, NULL, sb,
						xid, NULL);

	if (!inode) {
		inode = ERR_PTR(rc);
		goto out;
	}

#ifdef CONFIG_CIFS_FSCACHE
	/* populate tcon->resource_id */
	tcon->resource_id = CIFS_I(inode)->uniqueid;
#endif

	if (rc && tcon->ipc) {
		cFYI(1, "ipc connection - fake read inode");
		inode->i_mode |= S_IFDIR;
		inode->i_nlink = 2;
		inode->i_op = &cifs_ipc_inode_ops;
		inode->i_fop = &simple_dir_operations;
		inode->i_uid = cifs_sb->mnt_uid;
		inode->i_gid = cifs_sb->mnt_gid;
	} else if (rc) {
		iget_failed(inode);
		inode = ERR_PTR(rc);
	}

out:
	kfree(full_path);
	/* can not call macro FreeXid here since in a void func
	 * TODO: This is no longer true
	 */
	_FreeXid(xid);
	return inode;
}