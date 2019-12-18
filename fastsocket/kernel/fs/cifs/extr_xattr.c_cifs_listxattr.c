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
struct super_block {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSSMBQAllEAs (int,struct cifs_tcon*,char*,int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ,int) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int CIFS_MOUNT_NO_XATTR ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  PTR_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

ssize_t cifs_listxattr(struct dentry *direntry, char *data, size_t buf_size)
{
	ssize_t rc = -EOPNOTSUPP;
#ifdef CONFIG_CIFS_XATTR
	int xid;
	struct cifs_sb_info *cifs_sb;
	struct tcon_link *tlink;
	struct cifs_tcon *pTcon;
	struct super_block *sb;
	char *full_path;

	if (direntry == NULL)
		return -EIO;
	if (direntry->d_inode == NULL)
		return -EIO;
	sb = direntry->d_inode->i_sb;
	if (sb == NULL)
		return -EIO;

	cifs_sb = CIFS_SB(sb);
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_XATTR)
		return -EOPNOTSUPP;

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	pTcon = tlink_tcon(tlink);

	xid = GetXid();

	full_path = build_path_from_dentry(direntry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto list_ea_exit;
	}
	/* return dos attributes as pseudo xattr */
	/* return alt name if available as pseudo attr */

	/* if proc/fs/cifs/streamstoxattr is set then
		search server for EAs or streams to
		returns as xattrs */
	rc = CIFSSMBQAllEAs(xid, pTcon, full_path, NULL, data,
				buf_size, cifs_sb->local_nls,
				cifs_sb->mnt_cifs_flags &
					CIFS_MOUNT_MAP_SPECIAL_CHR);

list_ea_exit:
	kfree(full_path);
	FreeXid(xid);
	cifs_put_tlink(tlink);
#endif
	return rc;
}