#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; } ;
struct cifs_tcon {TYPE_1__* ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
struct cifsInodeInfo {void* cifsAttrs; } ;
struct cifsFileInfo {struct tcon_link* tlink; void* pid; int /*<<< orphan*/  netfid; } ;
typedef  void* __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_8__ {void* tgid; } ;
struct TYPE_7__ {int /*<<< orphan*/  Attributes; scalar_t__ CreationTime; void* ChangeTime; void* LastWriteTime; void* LastAccessTime; } ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ FILE_BASIC_INFO ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 int /*<<< orphan*/  CIFSSMBClose (int,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int CIFSSMBOpen (int,struct cifs_tcon*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int CIFSSMBSetFileInfo (int,struct cifs_tcon*,TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int CIFSSMBSetPathInfo (int,struct cifs_tcon*,char*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int CIFS_SES_NT4 ; 
 int /*<<< orphan*/  CREATE_NOT_DIR ; 
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int FILE_WRITE_ATTRIBUTES ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  cifsFileInfo_put (struct cifsFileInfo*) ; 
 int /*<<< orphan*/  cifs_UnixTimeToNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cpu_to_le32 (void*) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 struct cifsFileInfo* find_writable_file (struct cifsInodeInfo*,int) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

__attribute__((used)) static int
cifs_set_file_info(struct inode *inode, struct iattr *attrs, int xid,
		    char *full_path, __u32 dosattr)
{
	int rc;
	int oplock = 0;
	__u16 netfid;
	__u32 netpid;
	bool set_time = false;
	struct cifsFileInfo *open_file;
	struct cifsInodeInfo *cifsInode = CIFS_I(inode);
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink = NULL;
	struct cifs_tcon *pTcon;
	FILE_BASIC_INFO	info_buf;

	if (attrs == NULL)
		return -EINVAL;

	if (attrs->ia_valid & ATTR_ATIME) {
		set_time = true;
		info_buf.LastAccessTime =
			cpu_to_le64(cifs_UnixTimeToNT(attrs->ia_atime));
	} else
		info_buf.LastAccessTime = 0;

	if (attrs->ia_valid & ATTR_MTIME) {
		set_time = true;
		info_buf.LastWriteTime =
		    cpu_to_le64(cifs_UnixTimeToNT(attrs->ia_mtime));
	} else
		info_buf.LastWriteTime = 0;

	/*
	 * Samba throws this field away, but windows may actually use it.
	 * Do not set ctime unless other time stamps are changed explicitly
	 * (i.e. by utimes()) since we would then have a mix of client and
	 * server times.
	 */
	if (set_time && (attrs->ia_valid & ATTR_CTIME)) {
		cFYI(1, "CIFS - CTIME changed");
		info_buf.ChangeTime =
		    cpu_to_le64(cifs_UnixTimeToNT(attrs->ia_ctime));
	} else
		info_buf.ChangeTime = 0;

	info_buf.CreationTime = 0;	/* don't change */
	info_buf.Attributes = cpu_to_le32(dosattr);

	/*
	 * If the file is already open for write, just use that fileid
	 */
	open_file = find_writable_file(cifsInode, true);
	if (open_file) {
		netfid = open_file->netfid;
		netpid = open_file->pid;
		pTcon = tlink_tcon(open_file->tlink);
		goto set_via_filehandle;
	}

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink)) {
		rc = PTR_ERR(tlink);
		tlink = NULL;
		goto out;
	}
	pTcon = tlink_tcon(tlink);

	/*
	 * NT4 apparently returns success on this call, but it doesn't
	 * really work.
	 */
	if (!(pTcon->ses->flags & CIFS_SES_NT4)) {
		rc = CIFSSMBSetPathInfo(xid, pTcon, full_path,
				     &info_buf, cifs_sb->local_nls,
				     cifs_sb->mnt_cifs_flags &
					CIFS_MOUNT_MAP_SPECIAL_CHR);
		if (rc == 0) {
			cifsInode->cifsAttrs = dosattr;
			goto out;
		} else if (rc != -EOPNOTSUPP && rc != -EINVAL)
			goto out;
	}

	cFYI(1, "calling SetFileInfo since SetPathInfo for "
		 "times not supported by this server");
	rc = CIFSSMBOpen(xid, pTcon, full_path, FILE_OPEN,
			 SYNCHRONIZE | FILE_WRITE_ATTRIBUTES,
			 CREATE_NOT_DIR, &netfid, &oplock,
			 NULL, cifs_sb->local_nls,
			 cifs_sb->mnt_cifs_flags &
				CIFS_MOUNT_MAP_SPECIAL_CHR);

	if (rc != 0) {
		if (rc == -EIO)
			rc = -EINVAL;
		goto out;
	}

	netpid = current->tgid;

set_via_filehandle:
	rc = CIFSSMBSetFileInfo(xid, pTcon, &info_buf, netfid, netpid);
	if (!rc)
		cifsInode->cifsAttrs = dosattr;

	if (open_file == NULL)
		CIFSSMBClose(xid, pTcon, netfid);
	else
		cifsFileInfo_put(open_file);
out:
	if (tlink != NULL)
		cifs_put_tlink(tlink);
	return rc;
}