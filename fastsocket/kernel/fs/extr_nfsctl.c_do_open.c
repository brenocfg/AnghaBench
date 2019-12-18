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
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;
struct TYPE_3__ {int /*<<< orphan*/  mnt; int /*<<< orphan*/  dentry; } ;
struct nameidata {TYPE_1__ path; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct file* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int O_RDWR ; 
 int /*<<< orphan*/  current_cred () ; 
 struct file* dentry_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct vfsmount* do_kern_mount (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int may_open (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  path_put (TYPE_1__*) ; 
 int vfs_path_lookup (int /*<<< orphan*/ ,struct vfsmount*,char*,int /*<<< orphan*/ ,struct nameidata*) ; 

__attribute__((used)) static struct file *do_open(char *name, int flags)
{
	struct nameidata nd;
	struct vfsmount *mnt;
	int error;

	mnt = do_kern_mount("nfsd", 0, "nfsd", NULL);
	if (IS_ERR(mnt))
		return (struct file *)mnt;

	error = vfs_path_lookup(mnt->mnt_root, mnt, name, 0, &nd);
	mntput(mnt);	/* drop do_kern_mount reference */
	if (error)
		return ERR_PTR(error);

	if (flags == O_RDWR)
		error = may_open(&nd.path, MAY_READ|MAY_WRITE, flags);
	else
		error = may_open(&nd.path, MAY_WRITE, flags);

	if (!error)
		return dentry_open(nd.path.dentry, nd.path.mnt, flags,
				   current_cred());

	path_put(&nd.path);
	return ERR_PTR(error);
}