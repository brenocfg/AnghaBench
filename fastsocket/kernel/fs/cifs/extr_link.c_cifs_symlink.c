#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/ * d_op; } ;
struct cifs_tcon {scalar_t__ nocase; scalar_t__ unix_ext; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;

/* Variables and functions */
 int CIFSCreateMFSymLink (int,struct cifs_tcon*,char*,char const*,struct cifs_sb_info*) ; 
 int CIFSUnixCreateSymLink (int,struct cifs_tcon*,char*,char const*,int /*<<< orphan*/ ) ; 
 int CIFS_MOUNT_MF_SYMLINKS ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 char* build_path_from_dentry (struct dentry*) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int /*<<< orphan*/  cifs_ci_dentry_ops ; 
 int /*<<< orphan*/  cifs_dentry_ops ; 
 int cifs_get_inode_info (struct inode**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int cifs_get_inode_info_unix (struct inode**,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int
cifs_symlink(struct inode *inode, struct dentry *direntry, const char *symname)
{
	int rc = -EOPNOTSUPP;
	int xid;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink;
	struct cifs_tcon *pTcon;
	char *full_path = NULL;
	struct inode *newinode = NULL;

	xid = GetXid();

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink)) {
		rc = PTR_ERR(tlink);
		goto symlink_exit;
	}
	pTcon = tlink_tcon(tlink);

	full_path = build_path_from_dentry(direntry);
	if (full_path == NULL) {
		rc = -ENOMEM;
		goto symlink_exit;
	}

	cFYI(1, "Full path: %s", full_path);
	cFYI(1, "symname is %s", symname);

	/* BB what if DFS and this volume is on different share? BB */
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS)
		rc = CIFSCreateMFSymLink(xid, pTcon, full_path, symname,
					 cifs_sb);
	else if (pTcon->unix_ext)
		rc = CIFSUnixCreateSymLink(xid, pTcon, full_path, symname,
					   cifs_sb->local_nls);
	/* else
	   rc = CIFSCreateReparseSymLink(xid, pTcon, fromName, toName,
					cifs_sb_target->local_nls); */

	if (rc == 0) {
		if (pTcon->unix_ext)
			rc = cifs_get_inode_info_unix(&newinode, full_path,
						      inode->i_sb, xid);
		else
			rc = cifs_get_inode_info(&newinode, full_path, NULL,
						 inode->i_sb, xid, NULL);

		if (rc != 0) {
			cFYI(1, "Create symlink ok, getinodeinfo fail rc = %d",
			      rc);
		} else {
			if (pTcon->nocase)
				direntry->d_op = &cifs_ci_dentry_ops;
			else
				direntry->d_op = &cifs_dentry_ops;
			d_instantiate(direntry, newinode);
		}
	}
symlink_exit:
	kfree(full_path);
	cifs_put_tlink(tlink);
	FreeXid(xid);
	return rc;
}