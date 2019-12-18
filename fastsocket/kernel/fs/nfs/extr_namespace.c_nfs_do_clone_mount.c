#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct nfs_server {TYPE_2__* nfs_client; } ;
struct nfs_clone_mount {int dummy; } ;
struct TYPE_4__ {TYPE_1__* rpc_ops; } ;
struct TYPE_3__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct vfsmount* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_xdev_fs_type ; 
 int /*<<< orphan*/  nfs_xdev_fs_type ; 
 struct vfsmount* vfs_kern_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,struct nfs_clone_mount*) ; 

__attribute__((used)) static struct vfsmount *nfs_do_clone_mount(struct nfs_server *server,
					   const char *devname,
					   struct nfs_clone_mount *mountdata)
{
#ifdef CONFIG_NFS_V4
	struct vfsmount *mnt = ERR_PTR(-EINVAL);
	switch (server->nfs_client->rpc_ops->version) {
		case 2:
		case 3:
			mnt = vfs_kern_mount(&nfs_xdev_fs_type, 0, devname, mountdata);
			break;
		case 4:
			mnt = vfs_kern_mount(&nfs4_xdev_fs_type, 0, devname, mountdata);
	}
	return mnt;
#else
	return vfs_kern_mount(&nfs_xdev_fs_type, 0, devname, mountdata);
#endif
}