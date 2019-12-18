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
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
struct cifs_ntsd {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSSMBClose (int,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int CIFSSMBOpen (int,struct cifs_tcon*,char const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int CIFSSMBSetCIFSACL (int,struct cifs_tcon*,int /*<<< orphan*/ ,struct cifs_ntsd*,int /*<<< orphan*/ ,int) ; 
 int CIFS_ACL_GROUP ; 
 int CIFS_ACL_OWNER ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int CREATE_OPEN_BACKUP_INTENT ; 
 int /*<<< orphan*/  DBG2 ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/  FreeXid (int) ; 
 int GetXid () ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 int WRITE_DAC ; 
 int WRITE_OWNER ; 
 scalar_t__ backup_cred (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cERROR (int,char*) ; 
 int /*<<< orphan*/  cFYI (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int set_cifs_acl(struct cifs_ntsd *pnntsd, __u32 acllen,
			struct inode *inode, const char *path, int aclflag)
{
	int oplock = 0;
	int xid, rc, access_flags, create_options = 0;
	__u16 fid;
	struct cifs_tcon *tcon;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink = cifs_sb_tlink(cifs_sb);

	if (IS_ERR(tlink))
		return PTR_ERR(tlink);

	tcon = tlink_tcon(tlink);
	xid = GetXid();

	if (backup_cred(cifs_sb))
		create_options |= CREATE_OPEN_BACKUP_INTENT;

	if (aclflag == CIFS_ACL_OWNER || aclflag == CIFS_ACL_GROUP)
		access_flags = WRITE_OWNER;
	else
		access_flags = WRITE_DAC;

	rc = CIFSSMBOpen(xid, tcon, path, FILE_OPEN, access_flags,
			create_options, &fid, &oplock, NULL, cifs_sb->local_nls,
			cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR);
	if (rc) {
		cERROR(1, "Unable to open file to set ACL");
		goto out;
	}

	rc = CIFSSMBSetCIFSACL(xid, tcon, fid, pnntsd, acllen, aclflag);
	cFYI(DBG2, "SetCIFSACL rc = %d", rc);

	CIFSSMBClose(xid, tcon, fid);
out:
	FreeXid(xid);
	cifs_put_tlink(tlink);
	return rc;
}