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
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int CIFSSMBSetEA (int,struct cifs_tcon*,char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int CIFS_MOUNT_NO_XATTR ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  CIFS_XATTR_OS2_PREFIX ; 
 int /*<<< orphan*/  CIFS_XATTR_USER_PREFIX ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int cifs_removexattr(struct dentry *direntry, const char *ea_name)
{
	int rc = -EOPNOTSUPP;
#ifdef CONFIG_CIFS_XATTR
	int xid;
	struct cifs_sb_info *cifs_sb;
	struct tcon_link *tlink;
	struct cifs_tcon *pTcon;
	struct super_block *sb;
	char *full_path = NULL;

	if (direntry == NULL)
		return -EIO;
	if (direntry->d_inode == NULL)
		return -EIO;
	sb = direntry->d_inode->i_sb;
	if (sb == NULL)
		return -EIO;

	cifs_sb = CIFS_SB(sb);
	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	pTcon = tlink_tcon(tlink);

	xid = GetXid();

	full_path = build_path_from_dentry(direntry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto remove_ea_exit;
	}
	if (ea_name == NULL) {
		cFYI(1, "Null xattr names not supported");
	} else if (strncmp(ea_name, CIFS_XATTR_USER_PREFIX, 5)
		&& (strncmp(ea_name, CIFS_XATTR_OS2_PREFIX, 4))) {
		cFYI(1,
		     "illegal xattr request %s (only user namespace supported)",
		     ea_name);
		/* BB what if no namespace prefix? */
		/* Should we just pass them to server, except for
		system and perhaps security prefixes? */
	} else {
		if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NO_XATTR)
			goto remove_ea_exit;

		ea_name += 5; /* skip past user. prefix */
		rc = CIFSSMBSetEA(xid, pTcon, full_path, ea_name, NULL,
			(__u16)0, cifs_sb->local_nls,
			cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR);
	}
remove_ea_exit:
	kfree(full_path);
	FreeXid(xid);
	cifs_put_tlink(tlink);
#endif
	return rc;
}