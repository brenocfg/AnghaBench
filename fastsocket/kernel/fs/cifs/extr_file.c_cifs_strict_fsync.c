#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; struct cifsFileInfo* private_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__ d_name; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;
struct cifsFileInfo {int /*<<< orphan*/  netfid; int /*<<< orphan*/  tlink; } ;
struct TYPE_8__ {int /*<<< orphan*/  clientCanCacheRead; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int CIFSSMBFlush (int,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 TYPE_4__* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_NOSSYNC ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 int /*<<< orphan*/  cFYI (int,char*,int,...) ; 
 int cifs_invalidate_mapping (struct inode*) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 

int cifs_strict_fsync(struct file *file, struct dentry *dentry, int datasync)
{
	int xid;
	int rc = 0;
	struct cifs_tcon *tcon;
	struct cifsFileInfo *smbfile = file->private_data;
	struct inode *inode = file->f_path.dentry->d_inode;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	xid = GetXid();

	cFYI(1, "Sync file - name: %s datasync: 0x%x",
		dentry->d_name.name, datasync);

	if (!CIFS_I(inode)->clientCanCacheRead) {
		rc = cifs_invalidate_mapping(inode);
		if (rc) {
			cFYI(1, "rc: %d during invalidate phase", rc);
			rc = 0; /* don't care about it in fsync */
		}
	}

	tcon = tlink_tcon(smbfile->tlink);
	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NOSSYNC))
		rc = CIFSSMBFlush(xid, tcon, smbfile->netfid);

	FreeXid(xid);
	return rc;
}