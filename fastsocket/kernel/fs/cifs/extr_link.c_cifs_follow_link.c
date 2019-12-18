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
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {struct inode* d_inode; } ;
struct cifs_tcon {TYPE_1__* ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
struct TYPE_2__ {int capabilities; } ;

/* Variables and functions */
 int CAP_UNIX ; 
 int CIFSQueryMFSymLink (int,struct cifs_tcon*,char*,char**,int /*<<< orphan*/ ,int) ; 
 int CIFSSMBUnixQuerySymLink (int,struct cifs_tcon*,char*,char**,int /*<<< orphan*/ ) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int CIFS_MOUNT_MF_SYMLINKS ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int ENOMEM ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cFYI (int,char*,char*,struct inode*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  nd_set_link (struct nameidata*,char*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

void *
cifs_follow_link(struct dentry *direntry, struct nameidata *nd)
{
	struct inode *inode = direntry->d_inode;
	int rc = -ENOMEM;
	int xid;
	char *full_path = NULL;
	char *target_path = NULL;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink = NULL;
	struct cifs_tcon *tcon;

	xid = GetXid();

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink)) {
		rc = PTR_ERR(tlink);
		tlink = NULL;
		goto out;
	}
	tcon = tlink_tcon(tlink);

	/*
	 * For now, we just handle symlinks with unix extensions enabled.
	 * Eventually we should handle NTFS reparse points, and MacOS
	 * symlink support. For instance...
	 *
	 * rc = CIFSSMBQueryReparseLinkInfo(...)
	 *
	 * For now, just return -EACCES when the server doesn't support posix
	 * extensions. Note that we still allow querying symlinks when posix
	 * extensions are manually disabled. We could disable these as well
	 * but there doesn't seem to be any harm in allowing the client to
	 * read them.
	 */
	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS)
	    && !(tcon->ses->capabilities & CAP_UNIX)) {
		rc = -EACCES;
		goto out;
	}

	full_path = build_path_from_dentry(direntry);
	if (!full_path)
		goto out;

	cFYI(1, "Full path: %s inode = 0x%p", full_path, inode);

	rc = -EACCES;
	/*
	 * First try Minshall+French Symlinks, if configured
	 * and fallback to UNIX Extensions Symlinks.
	 */
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS)
		rc = CIFSQueryMFSymLink(xid, tcon, full_path, &target_path,
					cifs_sb->local_nls,
					cifs_sb->mnt_cifs_flags &
						CIFS_MOUNT_MAP_SPECIAL_CHR);

	if ((rc != 0) && (tcon->ses->capabilities & CAP_UNIX))
		rc = CIFSSMBUnixQuerySymLink(xid, tcon, full_path, &target_path,
					     cifs_sb->local_nls);

	kfree(full_path);
out:
	if (rc != 0) {
		kfree(target_path);
		target_path = ERR_PTR(rc);
	}

	FreeXid(xid);
	if (tlink)
		cifs_put_tlink(tlink);
	nd_set_link(nd, target_path);
	return NULL;
}