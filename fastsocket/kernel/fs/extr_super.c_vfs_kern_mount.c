#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {TYPE_1__* mnt_sb; int /*<<< orphan*/  mnt_root; struct vfsmount* mnt_parent; int /*<<< orphan*/  mnt_mountpoint; } ;
struct file_system_type {int fs_flags; int (* get_sb ) (struct file_system_type*,int,char const*,void*,struct vfsmount*) ;int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ s_maxbytes; int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct vfsmount* ERR_PTR (int) ; 
 int FS_BINARY_MOUNTDATA ; 
 int /*<<< orphan*/  MS_BORN ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* alloc_secdata () ; 
 struct vfsmount* alloc_vfsmnt (char const*) ; 
 int /*<<< orphan*/  deactivate_locked_super (TYPE_1__*) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_secdata (char*) ; 
 int /*<<< orphan*/  free_vfsmnt (struct vfsmount*) ; 
 int security_sb_copy_data (void*,char*) ; 
 int security_sb_kern_mount (TYPE_1__*,int,char*) ; 
 int stub1 (struct file_system_type*,int,char const*,void*,struct vfsmount*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct vfsmount *
vfs_kern_mount(struct file_system_type *type, int flags, const char *name, void *data)
{
	struct vfsmount *mnt;
	char *secdata = NULL;
	int error;

	if (!type)
		return ERR_PTR(-ENODEV);

	error = -ENOMEM;
	mnt = alloc_vfsmnt(name);
	if (!mnt)
		goto out;

	if (data && !(type->fs_flags & FS_BINARY_MOUNTDATA)) {
		secdata = alloc_secdata();
		if (!secdata)
			goto out_mnt;

		error = security_sb_copy_data(data, secdata);
		if (error)
			goto out_free_secdata;
	}

	error = type->get_sb(type, flags, name, data, mnt);
	if (error < 0)
		goto out_free_secdata;
	BUG_ON(!mnt->mnt_sb);
	mnt->mnt_sb->s_flags |= MS_BORN;

 	error = security_sb_kern_mount(mnt->mnt_sb, flags, secdata);
 	if (error)
 		goto out_sb;

	/*
	 * filesystems should never set s_maxbytes larger than MAX_LFS_FILESIZE
	 * but s_maxbytes was an unsigned long long for many releases. Throw
	 * this warning for a little while to try and catch filesystems that
	 * violate this rule. This warning should be either removed or
	 * converted to a BUG() in 2.6.34.
	 */
	WARN((mnt->mnt_sb->s_maxbytes < 0), "%s set sb->s_maxbytes to "
		"negative value (%lld)\n", type->name, mnt->mnt_sb->s_maxbytes);

	mnt->mnt_mountpoint = mnt->mnt_root;
	mnt->mnt_parent = mnt;
	up_write(&mnt->mnt_sb->s_umount);
	free_secdata(secdata);
	return mnt;
out_sb:
	dput(mnt->mnt_root);
	deactivate_locked_super(mnt->mnt_sb);
out_free_secdata:
	free_secdata(secdata);
out_mnt:
	free_vfsmnt(mnt);
out:
	return ERR_PTR(error);
}