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
struct vfsmount {int dummy; } ;
struct dfs_info3_param {int dummy; } ;
struct cifs_sb_info {int /*<<< orphan*/  mountdata; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 char* cifs_compose_mount_options (int /*<<< orphan*/ ,char const*,struct dfs_info3_param const*,char**) ; 
 int /*<<< orphan*/  cifs_fs_type ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct vfsmount* vfs_kern_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static struct vfsmount *cifs_dfs_do_refmount(struct cifs_sb_info *cifs_sb,
		const char *fullpath, const struct dfs_info3_param *ref)
{
	struct vfsmount *mnt;
	char *mountdata;
	char *devname = NULL;

	/* strip first '\' from fullpath */
	mountdata = cifs_compose_mount_options(cifs_sb->mountdata,
			fullpath + 1, ref, &devname);

	if (IS_ERR(mountdata))
		return (struct vfsmount *)mountdata;

	mnt = vfs_kern_mount(&cifs_fs_type, 0, devname, mountdata);
	kfree(mountdata);
	kfree(devname);
	return mnt;

}