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
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct file_system_type {int fs_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_subtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FS_HAS_SUBTYPE ; 
 int /*<<< orphan*/  IS_ERR (struct vfsmount*) ; 
 struct vfsmount* fs_set_subtype (struct vfsmount*,char const*) ; 
 struct file_system_type* get_fs_type (char const*) ; 
 int /*<<< orphan*/  put_filesystem (struct file_system_type*) ; 
 struct vfsmount* vfs_kern_mount (struct file_system_type*,int,char const*,void*) ; 

struct vfsmount *
do_kern_mount(const char *fstype, int flags, const char *name, void *data)
{
	struct file_system_type *type = get_fs_type(fstype);
	struct vfsmount *mnt;
	if (!type)
		return ERR_PTR(-ENODEV);
	mnt = vfs_kern_mount(type, flags, name, data);
	if (!IS_ERR(mnt) && (type->fs_flags & FS_HAS_SUBTYPE) &&
	    !mnt->mnt_sb->s_subtype)
		mnt = fs_set_subtype(mnt, fstype);
	put_filesystem(type);
	return mnt;
}