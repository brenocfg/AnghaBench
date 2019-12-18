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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {TYPE_2__* dentry; } ;
struct file {struct cifsFileInfo* private_data; TYPE_1__ f_path; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_fattr {int dummy; } ;
struct cifsFileInfo {int /*<<< orphan*/  netfid; int /*<<< orphan*/  tlink; } ;
struct TYPE_4__ {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  FILE_UNIX_BASIC_INFO ;

/* Variables and functions */
 int CIFSSMBUnixQFileInfo (int,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EREMOTE ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 int /*<<< orphan*/  cifs_create_dfs_fattr (struct cifs_fattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_fattr_to_inode (struct inode*,struct cifs_fattr*) ; 
 int /*<<< orphan*/  cifs_unix_basic_to_fattr (struct cifs_fattr*,int /*<<< orphan*/ *,struct cifs_sb_info*) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 

int cifs_get_file_info_unix(struct file *filp)
{
	int rc;
	int xid;
	FILE_UNIX_BASIC_INFO find_data;
	struct cifs_fattr fattr;
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct cifsFileInfo *cfile = filp->private_data;
	struct cifs_tcon *tcon = tlink_tcon(cfile->tlink);

	xid = GetXid();
	rc = CIFSSMBUnixQFileInfo(xid, tcon, cfile->netfid, &find_data);
	if (!rc) {
		cifs_unix_basic_to_fattr(&fattr, &find_data, cifs_sb);
	} else if (rc == -EREMOTE) {
		cifs_create_dfs_fattr(&fattr, inode->i_sb);
		rc = 0;
	}

	cifs_fattr_to_inode(inode, &fattr);
	FreeXid(xid);
	return rc;
}