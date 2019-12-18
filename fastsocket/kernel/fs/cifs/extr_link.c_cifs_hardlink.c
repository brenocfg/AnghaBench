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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct cifs_tcon {scalar_t__ unix_ext; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
struct cifsInodeInfo {scalar_t__ time; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 int CIFSCreateHardLink (int,struct cifs_tcon*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int CIFSUnixCreateHardLink (int,struct cifs_tcon*,char*,char*,int /*<<< orphan*/ ,int) ; 
 struct cifsInodeInfo* CIFS_I (TYPE_1__*) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int
cifs_hardlink(struct dentry *old_file, struct inode *inode,
	      struct dentry *direntry)
{
	int rc = -EACCES;
	int xid;
	char *fromName = NULL;
	char *toName = NULL;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink;
	struct cifs_tcon *pTcon;
	struct cifsInodeInfo *cifsInode;

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	pTcon = tlink_tcon(tlink);

	xid = GetXid();

	fromName = build_path_from_dentry(old_file);
	toName = build_path_from_dentry(direntry);
	if ((fromName == NULL) || (toName == NULL)) {
		rc = -ENOMEM;
		goto cifs_hl_exit;
	}

	if (pTcon->unix_ext)
		rc = CIFSUnixCreateHardLink(xid, pTcon, fromName, toName,
					    cifs_sb->local_nls,
					    cifs_sb->mnt_cifs_flags &
						CIFS_MOUNT_MAP_SPECIAL_CHR);
	else {
		rc = CIFSCreateHardLink(xid, pTcon, fromName, toName,
					cifs_sb->local_nls,
					cifs_sb->mnt_cifs_flags &
						CIFS_MOUNT_MAP_SPECIAL_CHR);
		if ((rc == -EIO) || (rc == -EINVAL))
			rc = -EOPNOTSUPP;
	}

	d_drop(direntry);	/* force new lookup from server of target */

	/* if source file is cached (oplocked) revalidate will not go to server
	   until the file is closed or oplock broken so update nlinks locally */
	if (old_file->d_inode) {
		cifsInode = CIFS_I(old_file->d_inode);
		if (rc == 0) {
			old_file->d_inode->i_nlink++;
/* BB should we make this contingent on superblock flag NOATIME? */
/*			old_file->d_inode->i_ctime = CURRENT_TIME;*/
			/* parent dir timestamps will update from srv
			within a second, would it really be worth it
			to set the parent dir cifs inode time to zero
			to force revalidate (faster) for it too? */
		}
		/* if not oplocked will force revalidate to get info
		   on source file from srv */
		cifsInode->time = 0;

		/* Will update parent dir timestamps from srv within a second.
		   Would it really be worth it to set the parent dir (cifs
		   inode) time field to zero to force revalidate on parent
		   directory faster ie
			CIFS_I(inode)->time = 0;  */
	}

cifs_hl_exit:
	kfree(fromName);
	kfree(toName);
	FreeXid(xid);
	cifs_put_tlink(tlink);
	return rc;
}