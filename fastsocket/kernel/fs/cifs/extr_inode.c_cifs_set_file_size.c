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
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_sb; } ;
struct iattr {int /*<<< orphan*/  ia_size; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
struct cifs_io_parms {int /*<<< orphan*/  length; scalar_t__ offset; struct cifs_tcon* tcon; int /*<<< orphan*/  pid; void* netfid; } ;
struct cifsInodeInfo {int /*<<< orphan*/  server_eof; } ;
struct cifsFileInfo {struct tcon_link* tlink; int /*<<< orphan*/  pid; void* netfid; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  void* __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSSMBClose (int,struct cifs_tcon*,void*) ; 
 int CIFSSMBSetEOF (int,struct cifs_tcon*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int CIFSSMBSetFileSize (int,struct cifs_tcon*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int CIFSSMBWrite (int,struct cifs_io_parms*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CREATE_NOT_DIR ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 int SMBLegacyOpen (int,struct cifs_tcon*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cFYI (int,char*,int) ; 
 int /*<<< orphan*/  cifsFileInfo_put (struct cifsFileInfo*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_truncate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cifs_vmtruncate (struct inode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct cifsFileInfo* find_writable_file (struct cifsInodeInfo*,int) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

__attribute__((used)) static int
cifs_set_file_size(struct inode *inode, struct iattr *attrs,
		   int xid, char *full_path)
{
	int rc;
	struct cifsFileInfo *open_file;
	struct cifsInodeInfo *cifsInode = CIFS_I(inode);
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink = NULL;
	struct cifs_tcon *pTcon = NULL;
	struct cifs_io_parms io_parms;

	/*
	 * To avoid spurious oplock breaks from server, in the case of
	 * inodes that we already have open, avoid doing path based
	 * setting of file size if we can do it by handle.
	 * This keeps our caching token (oplock) and avoids timeouts
	 * when the local oplock break takes longer to flush
	 * writebehind data than the SMB timeout for the SetPathInfo
	 * request would allow
	 */
	open_file = find_writable_file(cifsInode, true);
	if (open_file) {
		__u16 nfid = open_file->netfid;
		__u32 npid = open_file->pid;
		pTcon = tlink_tcon(open_file->tlink);
		rc = CIFSSMBSetFileSize(xid, pTcon, attrs->ia_size, nfid,
					npid, false);
		cifsFileInfo_put(open_file);
		cFYI(1, "SetFSize for attrs rc = %d", rc);
		if ((rc == -EINVAL) || (rc == -EOPNOTSUPP)) {
			unsigned int bytes_written;

			io_parms.netfid = nfid;
			io_parms.pid = npid;
			io_parms.tcon = pTcon;
			io_parms.offset = 0;
			io_parms.length = attrs->ia_size;
			rc = CIFSSMBWrite(xid, &io_parms, &bytes_written,
					  NULL, NULL, 1);
			cFYI(1, "Wrt seteof rc %d", rc);
		}
	} else
		rc = -EINVAL;

	if (rc != 0) {
		if (pTcon == NULL) {
			tlink = cifs_sb_tlink(cifs_sb);
			if (IS_ERR(tlink))
				return PTR_ERR(tlink);
			pTcon = tlink_tcon(tlink);
		}

		/* Set file size by pathname rather than by handle
		   either because no valid, writeable file handle for
		   it was found or because there was an error setting
		   it by handle */
		rc = CIFSSMBSetEOF(xid, pTcon, full_path, attrs->ia_size,
				   false, cifs_sb->local_nls,
				   cifs_sb->mnt_cifs_flags &
					CIFS_MOUNT_MAP_SPECIAL_CHR);
		cFYI(1, "SetEOF by path (setattrs) rc = %d", rc);
		if ((rc == -EINVAL) || (rc == -EOPNOTSUPP)) {
			__u16 netfid;
			int oplock = 0;

			rc = SMBLegacyOpen(xid, pTcon, full_path,
				FILE_OPEN, GENERIC_WRITE,
				CREATE_NOT_DIR, &netfid, &oplock, NULL,
				cifs_sb->local_nls,
				cifs_sb->mnt_cifs_flags &
					CIFS_MOUNT_MAP_SPECIAL_CHR);
			if (rc == 0) {
				unsigned int bytes_written;

				io_parms.netfid = netfid;
				io_parms.pid = current->tgid;
				io_parms.tcon = pTcon;
				io_parms.offset = 0;
				io_parms.length = attrs->ia_size;
				rc = CIFSSMBWrite(xid, &io_parms,
						  &bytes_written,
						  NULL, NULL,  1);
				cFYI(1, "wrt seteof rc %d", rc);
				CIFSSMBClose(xid, pTcon, netfid);
			}
		}
		if (tlink)
			cifs_put_tlink(tlink);
	}

	if (rc == 0) {
		cifsInode->server_eof = attrs->ia_size;
		rc = cifs_vmtruncate(inode, attrs->ia_size);
		cifs_truncate_page(inode->i_mapping, inode->i_size);
	}

	return rc;
}