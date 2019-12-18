#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {struct super_block* mnt_root; struct super_block* mnt_sb; } ;
struct super_block {int flags; int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; TYPE_1__* d_inode; struct super_block* s_fs_info; } ;
struct nfs_server {int flags; int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; TYPE_1__* d_inode; struct nfs_server* s_fs_info; } ;
struct nfs_sb_mountdata {int mntflags; struct super_block* server; } ;
struct nfs_clone_mount {struct super_block* sb; int /*<<< orphan*/  fh; int /*<<< orphan*/  authflavor; int /*<<< orphan*/  fattr; } ;
struct file_system_type {int dummy; } ;
struct dentry {int flags; int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; TYPE_1__* d_inode; struct dentry* s_fs_info; } ;
struct TYPE_9__ {TYPE_3__* nfs_client; } ;
struct TYPE_8__ {TYPE_2__* rpc_ops; } ;
struct TYPE_7__ {scalar_t__ dir_inode_ops; } ;
struct TYPE_6__ {scalar_t__ i_op; } ;

/* Variables and functions */
 int ESTALE ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  MS_ACTIVE ; 
 int MS_SYNCHRONOUS ; 
 int NFS_MOUNT_NOAC ; 
 int NFS_MOUNT_UNSHARED ; 
 TYPE_4__* NFS_SB (struct super_block*) ; 
 int PTR_ERR (struct super_block*) ; 
 int /*<<< orphan*/  bdi_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  dput (struct super_block*) ; 
 int nfs_bdi_register (struct super_block*) ; 
 struct super_block* nfs_clone_server (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_clone_super (struct super_block*,struct super_block*) ; 
 int nfs_compare_super (struct super_block*,void*) ; 
 int /*<<< orphan*/  nfs_free_server (struct super_block*) ; 
 int /*<<< orphan*/  nfs_fs_type ; 
 int /*<<< orphan*/  nfs_fscache_get_super_cookie (struct super_block*,int /*<<< orphan*/ *,struct nfs_clone_mount*) ; 
 struct super_block* nfs_get_root (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_set_super ; 
 int security_sb_clone_mnt_opts (struct super_block*,struct super_block*) ; 
 struct super_block* sget (int /*<<< orphan*/ *,int (*) (struct super_block*,void*),int /*<<< orphan*/ ,struct nfs_sb_mountdata*) ; 

__attribute__((used)) static int nfs_xdev_get_sb(struct file_system_type *fs_type, int flags,
			   const char *dev_name, void *raw_data,
			   struct vfsmount *mnt)
{
	struct nfs_clone_mount *data = raw_data;
	struct super_block *s;
	struct nfs_server *server;
	struct dentry *mntroot;
	int (*compare_super)(struct super_block *, void *) = nfs_compare_super;
	struct nfs_sb_mountdata sb_mntdata = {
		.mntflags = flags,
	};
	int error;

	dprintk("--> nfs_xdev_get_sb()\n");

	/* create a new volume representation */
	server = nfs_clone_server(NFS_SB(data->sb), data->fh, data->fattr, data->authflavor);
	if (IS_ERR(server)) {
		error = PTR_ERR(server);
		goto out_err_noserver;
	}
	sb_mntdata.server = server;

	if (server->flags & NFS_MOUNT_UNSHARED)
		compare_super = NULL;

	/* -o noac implies -o sync */
	if (server->flags & NFS_MOUNT_NOAC)
		sb_mntdata.mntflags |= MS_SYNCHRONOUS;

	/* Get a superblock - note that we may end up sharing one that already exists */
	s = sget(&nfs_fs_type, compare_super, nfs_set_super, &sb_mntdata);
	if (IS_ERR(s)) {
		error = PTR_ERR(s);
		goto out_err_nosb;
	}

	if (s->s_fs_info != server) {
		nfs_free_server(server);
		server = NULL;
	} else {
		error = nfs_bdi_register(server);
		if (error)
			goto error_splat_bdi;
	}

	if (!s->s_root) {
		/* initial superblock/root creation */
		nfs_clone_super(s, data->sb);
		nfs_fscache_get_super_cookie(s, NULL, data);
	}

	mntroot = nfs_get_root(s, data->fh);
	if (IS_ERR(mntroot)) {
		error = PTR_ERR(mntroot);
		goto error_splat_super;
	}
	if (mntroot->d_inode->i_op != NFS_SB(s)->nfs_client->rpc_ops->dir_inode_ops) {
		error = -ESTALE;
		goto error_splat_root;
	}

	s->s_flags |= MS_ACTIVE;
	mnt->mnt_sb = s;
	mnt->mnt_root = mntroot;

	/* clone any lsm security options from the parent to the new sb */
	error = security_sb_clone_mnt_opts(data->sb, s);
	if (error)
		goto error_splat_root;

	dprintk("<-- nfs_xdev_get_sb() = 0\n");
	return 0;

out_err_nosb:
	nfs_free_server(server);
out_err_noserver:
	dprintk("<-- nfs_xdev_get_sb() = %d [error]\n", error);
	return error;

error_splat_root:
	dput(mntroot);
error_splat_super:
	if (server && !s->s_root)
		bdi_unregister(&server->backing_dev_info);
error_splat_bdi:
	deactivate_locked_super(s);
	dprintk("<-- nfs_xdev_get_sb() = %d [splat]\n", error);
	return error;
}