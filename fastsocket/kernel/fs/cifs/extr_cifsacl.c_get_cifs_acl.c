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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_ntsd {int dummy; } ;
struct cifsFileInfo {int /*<<< orphan*/  netfid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  cifsFileInfo_put (struct cifsFileInfo*) ; 
 struct cifsFileInfo* find_readable_file (int /*<<< orphan*/ ,int) ; 
 struct cifs_ntsd* get_cifs_acl_by_fid (struct cifs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cifs_ntsd* get_cifs_acl_by_path (struct cifs_sb_info*,char const*,int /*<<< orphan*/ *) ; 

struct cifs_ntsd *get_cifs_acl(struct cifs_sb_info *cifs_sb,
				      struct inode *inode, const char *path,
				      u32 *pacllen)
{
	struct cifs_ntsd *pntsd = NULL;
	struct cifsFileInfo *open_file = NULL;

	if (inode)
		open_file = find_readable_file(CIFS_I(inode), true);
	if (!open_file)
		return get_cifs_acl_by_path(cifs_sb, path, pacllen);

	pntsd = get_cifs_acl_by_fid(cifs_sb, open_file->netfid, pacllen);
	cifsFileInfo_put(open_file);
	return pntsd;
}