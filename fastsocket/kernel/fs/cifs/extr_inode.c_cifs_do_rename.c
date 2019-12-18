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
struct TYPE_2__ {scalar_t__ name; } ;
struct dentry {scalar_t__ d_parent; TYPE_1__ d_name; int /*<<< orphan*/  d_sb; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSSMBClose (int,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int CIFSSMBOpen (int,struct cifs_tcon*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int CIFSSMBRename (int,struct cifs_tcon*,char const*,char const*,int /*<<< orphan*/ ,int) ; 
 int CIFSSMBRenameOpenFile (int,struct cifs_tcon*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CREATE_NOT_DIR ; 
 int /*<<< orphan*/  DELETE ; 
 int ETXTBSY ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

__attribute__((used)) static int
cifs_do_rename(int xid, struct dentry *from_dentry, const char *fromPath,
		struct dentry *to_dentry, const char *toPath)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(from_dentry->d_sb);
	struct tcon_link *tlink;
	struct cifs_tcon *pTcon;
	__u16 srcfid;
	int oplock, rc;

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	pTcon = tlink_tcon(tlink);

	/* try path-based rename first */
	rc = CIFSSMBRename(xid, pTcon, fromPath, toPath, cifs_sb->local_nls,
			   cifs_sb->mnt_cifs_flags &
				CIFS_MOUNT_MAP_SPECIAL_CHR);

	/*
	 * don't bother with rename by filehandle unless file is busy and
	 * source Note that cross directory moves do not work with
	 * rename by filehandle to various Windows servers.
	 */
	if (rc == 0 || rc != -ETXTBSY)
		goto do_rename_exit;

	/* open-file renames don't work across directories */
	if (to_dentry->d_parent != from_dentry->d_parent)
		goto do_rename_exit;

	/* open the file to be renamed -- we need DELETE perms */
	rc = CIFSSMBOpen(xid, pTcon, fromPath, FILE_OPEN, DELETE,
			 CREATE_NOT_DIR, &srcfid, &oplock, NULL,
			 cifs_sb->local_nls, cifs_sb->mnt_cifs_flags &
				CIFS_MOUNT_MAP_SPECIAL_CHR);

	if (rc == 0) {
		rc = CIFSSMBRenameOpenFile(xid, pTcon, srcfid,
				(const char *) to_dentry->d_name.name,
				cifs_sb->local_nls, cifs_sb->mnt_cifs_flags &
					CIFS_MOUNT_MAP_SPECIAL_CHR);

		CIFSSMBClose(xid, pTcon, srcfid);
	}
do_rename_exit:
	cifs_put_tlink(tlink);
	return rc;
}