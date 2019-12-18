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
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
typedef  int /*<<< orphan*/  FILE_ALL_INFO ;

/* Variables and functions */
 int CIFSSMBQPathInfo (int,struct cifs_tcon*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SMBQueryInformation (int,struct cifs_tcon*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_path_accessible(int xid, struct cifs_tcon *tcon,
		   struct cifs_sb_info *cifs_sb, const char *full_path)
{
	int rc;
	FILE_ALL_INFO *pfile_info;

	pfile_info = kmalloc(sizeof(FILE_ALL_INFO), GFP_KERNEL);
	if (pfile_info == NULL)
		return -ENOMEM;

	rc = CIFSSMBQPathInfo(xid, tcon, full_path, pfile_info,
			      0 /* not legacy */, cifs_sb->local_nls,
			      cifs_sb->mnt_cifs_flags &
				CIFS_MOUNT_MAP_SPECIAL_CHR);

	if (rc == -EOPNOTSUPP || rc == -EINVAL)
		rc = SMBQueryInformation(xid, tcon, full_path, pfile_info,
				cifs_sb->local_nls, cifs_sb->mnt_cifs_flags &
				  CIFS_MOUNT_MAP_SPECIAL_CHR);
	kfree(pfile_info);
	return rc;
}