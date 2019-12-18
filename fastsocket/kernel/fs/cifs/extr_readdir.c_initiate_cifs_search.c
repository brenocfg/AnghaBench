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
struct tcon_link {int dummy; } ;
struct TYPE_5__ {TYPE_3__* dentry; } ;
struct file {int /*<<< orphan*/  f_pos; TYPE_1__ f_path; struct cifsFileInfo* private_data; } ;
struct cifs_tcon {TYPE_2__* ses; scalar_t__ unix_ext; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
struct TYPE_8__ {int endOfSearch; int /*<<< orphan*/  info_level; } ;
struct cifsFileInfo {int invalidHandle; TYPE_4__ srch_inf; int /*<<< orphan*/  netfid; struct tcon_link* tlink; } ;
struct TYPE_7__ {int /*<<< orphan*/  d_sb; } ;
struct TYPE_6__ {int capabilities; } ;

/* Variables and functions */
 int CAP_NT_FIND ; 
 int CAP_NT_SMBS ; 
 int CIFSFindFirst (int const,struct cifs_tcon*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CIFS_DIR_SEP (struct cifs_sb_info*) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int CIFS_MOUNT_SERVER_INUM ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  SMB_FIND_FILE_DIRECTORY_INFO ; 
 int /*<<< orphan*/  SMB_FIND_FILE_ID_FULL_DIR_INFO ; 
 int /*<<< orphan*/  SMB_FIND_FILE_INFO_STANDARD ; 
 int /*<<< orphan*/  SMB_FIND_FILE_UNIX ; 
 char* build_path_from_dentry (TYPE_3__*) ; 
 int /*<<< orphan*/  cFYI (int,char*,char*,int /*<<< orphan*/ ) ; 
 struct tcon_link* cifs_get_tlink (struct tcon_link*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct cifsFileInfo* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

__attribute__((used)) static int initiate_cifs_search(const int xid, struct file *file)
{
	int rc = 0;
	char *full_path = NULL;
	struct cifsFileInfo *cifsFile;
	struct cifs_sb_info *cifs_sb = CIFS_SB(file->f_path.dentry->d_sb);
	struct tcon_link *tlink = NULL;
	struct cifs_tcon *pTcon;

	if (file->private_data == NULL) {
		tlink = cifs_sb_tlink(cifs_sb);
		if (IS_ERR(tlink))
			return PTR_ERR(tlink);

		cifsFile = kzalloc(sizeof(struct cifsFileInfo), GFP_KERNEL);
		if (cifsFile == NULL) {
			rc = -ENOMEM;
			goto error_exit;
		}
		file->private_data = cifsFile;
		cifsFile->tlink = cifs_get_tlink(tlink);
		pTcon = tlink_tcon(tlink);
	} else {
		cifsFile = file->private_data;
		pTcon = tlink_tcon(cifsFile->tlink);
	}

	cifsFile->invalidHandle = true;
	cifsFile->srch_inf.endOfSearch = false;

	full_path = build_path_from_dentry(file->f_path.dentry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto error_exit;
	}

	cFYI(1, "Full path: %s start at: %lld", full_path, file->f_pos);

ffirst_retry:
	/* test for Unix extensions */
	/* but now check for them on the share/mount not on the SMB session */
/*	if (pTcon->ses->capabilities & CAP_UNIX) { */
	if (pTcon->unix_ext)
		cifsFile->srch_inf.info_level = SMB_FIND_FILE_UNIX;
	else if ((pTcon->ses->capabilities &
			(CAP_NT_SMBS | CAP_NT_FIND)) == 0) {
		cifsFile->srch_inf.info_level = SMB_FIND_FILE_INFO_STANDARD;
	} else if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM) {
		cifsFile->srch_inf.info_level = SMB_FIND_FILE_ID_FULL_DIR_INFO;
	} else /* not srvinos - BB fixme add check for backlevel? */ {
		cifsFile->srch_inf.info_level = SMB_FIND_FILE_DIRECTORY_INFO;
	}

	rc = CIFSFindFirst(xid, pTcon, full_path, cifs_sb->local_nls,
		&cifsFile->netfid, &cifsFile->srch_inf,
		cifs_sb->mnt_cifs_flags &
			CIFS_MOUNT_MAP_SPECIAL_CHR, CIFS_DIR_SEP(cifs_sb));
	if (rc == 0)
		cifsFile->invalidHandle = false;
	/* BB add following call to handle readdir on new NTFS symlink errors
	else if STATUS_STOPPED_ON_SYMLINK
		call get_symlink_reparse_path and retry with new path */
	else if ((rc == -EOPNOTSUPP) &&
		(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM)) {
		cifs_sb->mnt_cifs_flags &= ~CIFS_MOUNT_SERVER_INUM;
		goto ffirst_retry;
	}
error_exit:
	kfree(full_path);
	cifs_put_tlink(tlink);
	return rc;
}