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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
struct cifs_fattr {int dummy; } ;
typedef  int /*<<< orphan*/  FILE_UNIX_BASIC_INFO ;

/* Variables and functions */
 int CIFSCheckMFSymlink (struct cifs_fattr*,unsigned char const*,struct cifs_sb_info*,int) ; 
 int CIFSSMBUnixQPathInfo (int,struct cifs_tcon*,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int CIFS_MOUNT_MF_SYMLINKS ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 int ENOMEM ; 
 int EREMOTE ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int /*<<< orphan*/  cifs_create_dfs_fattr (struct cifs_fattr*,struct super_block*) ; 
 int /*<<< orphan*/  cifs_fattr_to_inode (struct inode*,struct cifs_fattr*) ; 
 int /*<<< orphan*/  cifs_fill_uniqueid (struct super_block*,struct cifs_fattr*) ; 
 struct inode* cifs_iget (struct super_block*,struct cifs_fattr*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_unix_basic_to_fattr (struct cifs_fattr*,int /*<<< orphan*/ *,struct cifs_sb_info*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int cifs_get_inode_info_unix(struct inode **pinode,
			     const unsigned char *full_path,
			     struct super_block *sb, int xid)
{
	int rc;
	FILE_UNIX_BASIC_INFO find_data;
	struct cifs_fattr fattr;
	struct cifs_tcon *tcon;
	struct tcon_link *tlink;
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);

	cFYI(1, "Getting info on %s", full_path);

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	/* could have done a find first instead but this returns more info */
	rc = CIFSSMBUnixQPathInfo(xid, tcon, full_path, &find_data,
				  cifs_sb->local_nls, cifs_sb->mnt_cifs_flags &
					CIFS_MOUNT_MAP_SPECIAL_CHR);
	cifs_put_tlink(tlink);

	if (!rc) {
		cifs_unix_basic_to_fattr(&fattr, &find_data, cifs_sb);
	} else if (rc == -EREMOTE) {
		cifs_create_dfs_fattr(&fattr, sb);
		rc = 0;
	} else {
		return rc;
	}

	/* check for Minshall+French symlinks */
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MF_SYMLINKS) {
		int tmprc = CIFSCheckMFSymlink(&fattr, full_path, cifs_sb, xid);
		if (tmprc)
			cFYI(1, "CIFSCheckMFSymlink: %d", tmprc);
	}

	if (*pinode == NULL) {
		/* get new inode */
		cifs_fill_uniqueid(sb, &fattr);
		*pinode = cifs_iget(sb, &fattr);
		if (!*pinode)
			rc = -ENOMEM;
	} else {
		/* we already have inode, update it */
		cifs_fattr_to_inode(*pinode, &fattr);
	}

	return rc;
}