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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mapping; } ;
struct TYPE_7__ {int /*<<< orphan*/  Capability; } ;
struct cifs_tcon {scalar_t__ unix_ext; TYPE_3__ fsUnixInfo; TYPE_2__* ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; int /*<<< orphan*/  mnt_file_mode; } ;
struct cifsInodeInfo {int dummy; } ;
struct cifsFileInfo {int invalidHandle; unsigned int f_flags; int /*<<< orphan*/  fh_mutex; int /*<<< orphan*/  netfid; TYPE_4__* dentry; int /*<<< orphan*/  tlink; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_8__ {struct inode* d_inode; } ;
struct TYPE_6__ {int capabilities; TYPE_1__* server; } ;
struct TYPE_5__ {scalar_t__ oplocks; } ;

/* Variables and functions */
 int CAP_UNIX ; 
 int CIFSSMBOpen (int,struct cifs_tcon*,char*,int,int,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int CIFS_UNIX_POSIX_PATH_OPS_CAP ; 
 int CREATE_NOT_DIR ; 
 int CREATE_OPEN_BACKUP_INTENT ; 
 int EACCES ; 
 int ENOMEM ; 
 int FILE_OPEN ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 unsigned int O_CREAT ; 
 unsigned int O_EXCL ; 
 unsigned int O_TRUNC ; 
 int REQ_OPLOCK ; 
 scalar_t__ backup_cred (struct cifs_sb_info*) ; 
 char* build_path_from_dentry (TYPE_4__*) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int cifs_convert_flags (unsigned int) ; 
 int cifs_get_inode_info (struct inode**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int cifs_get_inode_info_unix (struct inode**,char*,int /*<<< orphan*/ ,int) ; 
 int cifs_posix_open (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cifs_relock_file (struct cifsFileInfo*) ; 
 int /*<<< orphan*/  cifs_set_oplock_level (struct cifsInodeInfo*,int) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cifs_reopen_file(struct cifsFileInfo *pCifsFile, bool can_flush)
{
	int rc = -EACCES;
	int xid;
	__u32 oplock;
	struct cifs_sb_info *cifs_sb;
	struct cifs_tcon *tcon;
	struct cifsInodeInfo *pCifsInode;
	struct inode *inode;
	char *full_path = NULL;
	int desiredAccess;
	int disposition = FILE_OPEN;
	int create_options = CREATE_NOT_DIR;
	__u16 netfid;

	xid = GetXid();
	mutex_lock(&pCifsFile->fh_mutex);
	if (!pCifsFile->invalidHandle) {
		mutex_unlock(&pCifsFile->fh_mutex);
		rc = 0;
		FreeXid(xid);
		return rc;
	}

	inode = pCifsFile->dentry->d_inode;
	cifs_sb = CIFS_SB(inode->i_sb);
	tcon = tlink_tcon(pCifsFile->tlink);

/* can not grab rename sem here because various ops, including
   those that already have the rename sem can end up causing writepage
   to get called and if the server was down that means we end up here,
   and we can never tell if the caller already has the rename_sem */
	full_path = build_path_from_dentry(pCifsFile->dentry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		mutex_unlock(&pCifsFile->fh_mutex);
		FreeXid(xid);
		return rc;
	}

	cFYI(1, "inode = 0x%p file flags 0x%x for %s",
		 inode, pCifsFile->f_flags, full_path);

	if (tcon->ses->server->oplocks)
		oplock = REQ_OPLOCK;
	else
		oplock = 0;

	if (tcon->unix_ext && (tcon->ses->capabilities & CAP_UNIX) &&
	    (CIFS_UNIX_POSIX_PATH_OPS_CAP &
			le64_to_cpu(tcon->fsUnixInfo.Capability))) {

		/*
		 * O_CREAT, O_EXCL and O_TRUNC already had their effect on the
		 * original open. Must mask them off for a reopen.
		 */
		unsigned int oflags = pCifsFile->f_flags &
						~(O_CREAT | O_EXCL | O_TRUNC);

		rc = cifs_posix_open(full_path, NULL, inode->i_sb,
				cifs_sb->mnt_file_mode /* ignored */,
				oflags, &oplock, &netfid, xid);
		if (rc == 0) {
			cFYI(1, "posix reopen succeeded");
			goto reopen_success;
		}
		/* fallthrough to retry open the old way on errors, especially
		   in the reconnect path it is important to retry hard */
	}

	desiredAccess = cifs_convert_flags(pCifsFile->f_flags);

	if (backup_cred(cifs_sb))
		create_options |= CREATE_OPEN_BACKUP_INTENT;

	/* Can not refresh inode by passing in file_info buf to be returned
	   by SMBOpen and then calling get_inode_info with returned buf
	   since file might have write behind data that needs to be flushed
	   and server version of file size can be stale. If we knew for sure
	   that inode was not dirty locally we could do this */

	rc = CIFSSMBOpen(xid, tcon, full_path, disposition, desiredAccess,
			 create_options, &netfid, &oplock, NULL,
			 cifs_sb->local_nls, cifs_sb->mnt_cifs_flags &
				CIFS_MOUNT_MAP_SPECIAL_CHR);
	if (rc) {
		mutex_unlock(&pCifsFile->fh_mutex);
		cFYI(1, "cifs_open returned 0x%x", rc);
		cFYI(1, "oplock: %d", oplock);
		goto reopen_error_exit;
	}

reopen_success:
	pCifsFile->netfid = netfid;
	pCifsFile->invalidHandle = false;
	mutex_unlock(&pCifsFile->fh_mutex);
	pCifsInode = CIFS_I(inode);

	if (can_flush) {
		rc = filemap_write_and_wait(inode->i_mapping);
		mapping_set_error(inode->i_mapping, rc);

		if (tcon->unix_ext)
			rc = cifs_get_inode_info_unix(&inode,
				full_path, inode->i_sb, xid);
		else
			rc = cifs_get_inode_info(&inode,
				full_path, NULL, inode->i_sb,
				xid, NULL);
	} /* else we are writing out data to server already
	     and could deadlock if we tried to flush data, and
	     since we do not know if we have data that would
	     invalidate the current end of file on the server
	     we can not go to the server to get the new inod
	     info */

	cifs_set_oplock_level(pCifsInode, oplock);

	cifs_relock_file(pCifsFile);

reopen_error_exit:
	kfree(full_path);
	FreeXid(xid);
	return rc;
}