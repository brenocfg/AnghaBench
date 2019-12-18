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
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct nameidata {TYPE_1__ path; } ;
struct cache_detail {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int PTR_ERR (struct vfsmount*) ; 
 int /*<<< orphan*/  path_put (TYPE_1__*) ; 
 struct vfsmount* rpc_get_mount () ; 
 int /*<<< orphan*/  rpc_put_mount () ; 
 int sunrpc_cache_register_pipefs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct cache_detail*) ; 
 int vfs_path_lookup (int /*<<< orphan*/ ,struct vfsmount*,char*,int /*<<< orphan*/ ,struct nameidata*) ; 

int nfs_cache_register(struct cache_detail *cd)
{
	struct nameidata nd;
	struct vfsmount *mnt;
	int ret;

	mnt = rpc_get_mount();
	if (IS_ERR(mnt))
		return PTR_ERR(mnt);
	ret = vfs_path_lookup(mnt->mnt_root, mnt, "/cache", 0, &nd);
	if (ret)
		goto err;
	ret = sunrpc_cache_register_pipefs(nd.path.dentry,
			cd->name, 0600, cd);
	path_put(&nd.path);
	if (!ret)
		return ret;
err:
	rpc_put_mount();
	return ret;
}