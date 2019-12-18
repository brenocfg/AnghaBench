#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct TYPE_6__ {TYPE_5__* dentry; } ;
struct file {int /*<<< orphan*/  f_flags; TYPE_1__ f_path; } ;
struct cifs_unix_set_info_args {int /*<<< orphan*/  device; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  Capability; } ;
struct cifs_tcon {int broken_posix_open; scalar_t__ unix_ext; TYPE_4__* ses; TYPE_3__ fsUnixInfo; } ;
struct cifs_sb_info {int /*<<< orphan*/  mnt_file_mode; } ;
struct cifsInodeInfo {int dummy; } ;
struct cifsFileInfo {int /*<<< orphan*/  pid; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_10__ {int /*<<< orphan*/  d_inode; } ;
struct TYPE_9__ {int capabilities; scalar_t__ serverNOS; int /*<<< orphan*/  serverName; TYPE_2__* server; } ;
struct TYPE_7__ {scalar_t__ oplocks; } ;

/* Variables and functions */
 int CAP_UNIX ; 
 int /*<<< orphan*/  CIFSSMBClose (int,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIFSSMBUnixSetFileInfo (int,struct cifs_tcon*,struct cifs_unix_set_info_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CIFS_CREATE_ACTION ; 
 struct cifsInodeInfo* CIFS_I (int /*<<< orphan*/ ) ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int CIFS_UNIX_POSIX_PATH_OPS_CAP ; 
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EREMOTE ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  NO_CHANGE_64 ; 
 int PTR_ERR (struct tcon_link*) ; 
 int REQ_OPLOCK ; 
 char* build_path_from_dentry (TYPE_5__*) ; 
 int /*<<< orphan*/  cERROR (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int /*<<< orphan*/  cifs_fscache_set_inode_cookie (struct inode*,struct file*) ; 
 struct cifsFileInfo* cifs_new_fileinfo (int /*<<< orphan*/ ,struct file*,struct tcon_link*,int) ; 
 int cifs_nt_open (char*,struct inode*,struct cifs_sb_info*,struct cifs_tcon*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int) ; 
 int cifs_posix_open (char*,struct inode**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int cifs_open(struct inode *inode, struct file *file)
{
	int rc = -EACCES;
	int xid;
	__u32 oplock;
	struct cifs_sb_info *cifs_sb;
	struct cifs_tcon *tcon;
	struct tcon_link *tlink;
	struct cifsFileInfo *pCifsFile = NULL;
	struct cifsInodeInfo *pCifsInode;
	char *full_path = NULL;
	bool posix_open_ok = false;
	__u16 netfid;

	xid = GetXid();

	cifs_sb = CIFS_SB(inode->i_sb);
	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink)) {
		FreeXid(xid);
		return PTR_ERR(tlink);
	}
	tcon = tlink_tcon(tlink);

	pCifsInode = CIFS_I(file->f_path.dentry->d_inode);

	full_path = build_path_from_dentry(file->f_path.dentry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto out;
	}

	cFYI(1, "inode = 0x%p file flags are 0x%x for %s",
		 inode, file->f_flags, full_path);

	if (tcon->ses->server->oplocks)
		oplock = REQ_OPLOCK;
	else
		oplock = 0;

	if (!tcon->broken_posix_open && tcon->unix_ext &&
	    (tcon->ses->capabilities & CAP_UNIX) &&
	    (CIFS_UNIX_POSIX_PATH_OPS_CAP &
			le64_to_cpu(tcon->fsUnixInfo.Capability))) {
		/* can not refresh inode info since size could be stale */
		rc = cifs_posix_open(full_path, &inode, inode->i_sb,
				cifs_sb->mnt_file_mode /* ignored */,
				file->f_flags, &oplock, &netfid, xid);
		if (rc == 0) {
			cFYI(1, "posix open succeeded");
			posix_open_ok = true;
		} else if ((rc == -EINVAL) || (rc == -EOPNOTSUPP)) {
			if (tcon->ses->serverNOS)
				cERROR(1, "server %s of type %s returned"
					   " unexpected error on SMB posix open"
					   ", disabling posix open support."
					   " Check if server update available.",
					   tcon->ses->serverName,
					   tcon->ses->serverNOS);
			tcon->broken_posix_open = true;
		} else if ((rc != -EIO) && (rc != -EREMOTE) &&
			 (rc != -EOPNOTSUPP)) /* path not found or net err */
			goto out;
		/* else fallthrough to retry open the old way on network i/o
		   or DFS errors */
	}

	if (!posix_open_ok) {
		rc = cifs_nt_open(full_path, inode, cifs_sb, tcon,
				  file->f_flags, &oplock, &netfid, xid);
		if (rc)
			goto out;
	}

	pCifsFile = cifs_new_fileinfo(netfid, file, tlink, oplock);
	if (pCifsFile == NULL) {
		CIFSSMBClose(xid, tcon, netfid);
		rc = -ENOMEM;
		goto out;
	}

	cifs_fscache_set_inode_cookie(inode, file);

	if ((oplock & CIFS_CREATE_ACTION) && !posix_open_ok && tcon->unix_ext) {
		/* time to set mode which we can not set earlier due to
		   problems creating new read-only files */
		struct cifs_unix_set_info_args args = {
			.mode	= inode->i_mode,
			.uid	= NO_CHANGE_64,
			.gid	= NO_CHANGE_64,
			.ctime	= NO_CHANGE_64,
			.atime	= NO_CHANGE_64,
			.mtime	= NO_CHANGE_64,
			.device	= 0,
		};
		CIFSSMBUnixSetFileInfo(xid, tcon, &args, netfid,
					pCifsFile->pid);
	}

out:
	kfree(full_path);
	FreeXid(xid);
	cifs_put_tlink(tlink);
	return rc;
}