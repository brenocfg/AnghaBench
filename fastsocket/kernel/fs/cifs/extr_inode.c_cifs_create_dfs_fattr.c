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
struct super_block {int dummy; } ;
struct cifs_sb_info {int /*<<< orphan*/  mnt_gid; int /*<<< orphan*/  mnt_uid; } ;
struct cifs_fattr {int cf_mode; int cf_nlink; int /*<<< orphan*/  cf_flags; void* cf_mtime; void* cf_ctime; void* cf_atime; int /*<<< orphan*/  cf_gid; int /*<<< orphan*/  cf_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_FATTR_DFS_REFERRAL ; 
 struct cifs_sb_info* CIFS_SB (struct super_block*) ; 
 void* CURRENT_TIME ; 
 int S_IFDIR ; 
 int S_IRWXU ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  memset (struct cifs_fattr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cifs_create_dfs_fattr(struct cifs_fattr *fattr, struct super_block *sb)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);

	cFYI(1, "creating fake fattr for DFS referral");

	memset(fattr, 0, sizeof(*fattr));
	fattr->cf_mode = S_IFDIR | S_IXUGO | S_IRWXU;
	fattr->cf_uid = cifs_sb->mnt_uid;
	fattr->cf_gid = cifs_sb->mnt_gid;
	fattr->cf_atime = CURRENT_TIME;
	fattr->cf_ctime = CURRENT_TIME;
	fattr->cf_mtime = CURRENT_TIME;
	fattr->cf_nlink = 2;
	fattr->cf_flags |= CIFS_FATTR_DFS_REFERRAL;
}