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
struct path {int /*<<< orphan*/  dentry; TYPE_1__* mnt; } ;
struct nsproxy {struct mnt_namespace* mnt_ns; } ;
struct mnt_namespace {TYPE_1__* root; } ;
struct fs_struct {int users; } ;
struct TYPE_4__ {struct fs_struct* fs; } ;
struct TYPE_3__ {int /*<<< orphan*/  mnt_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_CHROOT ; 
 int EINVAL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 scalar_t__ d_mountpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ follow_down (struct path*) ; 
 int /*<<< orphan*/  get_mnt_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  put_mnt_ns (struct mnt_namespace*) ; 
 int /*<<< orphan*/  set_fs_pwd (struct fs_struct*,struct path*) ; 
 int /*<<< orphan*/  set_fs_root (struct fs_struct*,struct path*) ; 

__attribute__((used)) static int mntns_install(struct nsproxy *nsproxy, void *ns)
{
	struct fs_struct *fs = current->fs;
	struct mnt_namespace *mnt_ns = ns;
	struct path root;

	if (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_CHROOT))
		return -EINVAL;

	if (fs->users != 1)
		return -EINVAL;

	get_mnt_ns(mnt_ns);
	put_mnt_ns(nsproxy->mnt_ns);
	nsproxy->mnt_ns = mnt_ns;

	/* Find the root */
	root.mnt    = mnt_ns->root;
	root.dentry = mnt_ns->root->mnt_root;
	path_get(&root);
	while(d_mountpoint(root.dentry) && follow_down(&root))
		;

	/* Update the pwd and root */
	set_fs_pwd(fs, &root);
	set_fs_root(fs, &root);

	path_put(&root);
	return 0;
}