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
struct vfsmount {struct super_block* mnt_root; struct super_block* mnt_sb; } ;
struct super_block {int flags; int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; struct super_block* s_fs_info; } ;
struct nfs_server {int flags; int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; struct nfs_server* s_fs_info; } ;
struct nfs_sb_mountdata {int mntflags; struct super_block* server; } ;
struct nfs_parsed_mount_data {int version; int /*<<< orphan*/  lsm_opts; int /*<<< orphan*/ * fscache_uniq; } ;
struct nfs_fh {int dummy; } ;
struct file_system_type {int dummy; } ;
struct dentry {int flags; int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_flags; struct dentry* s_fs_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  MS_ACTIVE ; 
 int MS_SYNCHRONOUS ; 
 int /*<<< orphan*/  NFS_DEFAULT_VERSION ; 
 int NFS_MOUNT_NOAC ; 
 int NFS_MOUNT_UNSHARED ; 
 int PTR_ERR (struct super_block*) ; 
 int /*<<< orphan*/  bdi_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dput (struct super_block*) ; 
 int nfs4_try_mount (int,char const*,struct nfs_parsed_mount_data*,struct vfsmount*) ; 
 struct nfs_fh* nfs_alloc_fhandle () ; 
 struct nfs_parsed_mount_data* nfs_alloc_parsed_mount_data (int /*<<< orphan*/ ) ; 
 int nfs_bdi_register (struct super_block*) ; 
 int nfs_compare_super (struct super_block*,void*) ; 
 struct super_block* nfs_create_server (struct nfs_parsed_mount_data*,struct nfs_fh*) ; 
 int /*<<< orphan*/  nfs_fill_super (struct super_block*,struct nfs_parsed_mount_data*) ; 
 int /*<<< orphan*/  nfs_free_fhandle (struct nfs_fh*) ; 
 int /*<<< orphan*/  nfs_free_parsed_mount_data (struct nfs_parsed_mount_data*) ; 
 int /*<<< orphan*/  nfs_free_server (struct super_block*) ; 
 int /*<<< orphan*/  nfs_fscache_get_super_cookie (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct super_block* nfs_get_root (struct super_block*,struct nfs_fh*) ; 
 int /*<<< orphan*/  nfs_set_super ; 
 int nfs_validate_mount_data (void*,struct nfs_parsed_mount_data*,struct nfs_fh*,char const*) ; 
 int security_sb_set_mnt_opts (struct super_block*,int /*<<< orphan*/ *) ; 
 struct super_block* sget (struct file_system_type*,int (*) (struct super_block*,void*),int /*<<< orphan*/ ,struct nfs_sb_mountdata*) ; 

__attribute__((used)) static int nfs_get_sb(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *raw_data, struct vfsmount *mnt)
{
	struct nfs_server *server = NULL;
	struct super_block *s;
	struct nfs_parsed_mount_data *data;
	struct nfs_fh *mntfh;
	struct dentry *mntroot;
	int (*compare_super)(struct super_block *, void *) = nfs_compare_super;
	struct nfs_sb_mountdata sb_mntdata = {
		.mntflags = flags,
	};
	int error = -ENOMEM;

	data = nfs_alloc_parsed_mount_data(NFS_DEFAULT_VERSION);
	mntfh = nfs_alloc_fhandle();
	if (data == NULL || mntfh == NULL)
		goto out;

	/* Validate the mount data */
	error = nfs_validate_mount_data(raw_data, data, mntfh, dev_name);
	if (error < 0)
		goto out;

#ifdef CONFIG_NFS_V4
	if (data->version == 4) {
		error = nfs4_try_mount(flags, dev_name, data, mnt);
		goto out;
	}
#endif	/* CONFIG_NFS_V4 */

	/* Get a volume representation */
	server = nfs_create_server(data, mntfh);
	if (IS_ERR(server)) {
		error = PTR_ERR(server);
		goto out;
	}
	sb_mntdata.server = server;

	if (server->flags & NFS_MOUNT_UNSHARED)
		compare_super = NULL;

	/* -o noac implies -o sync */
	if (server->flags & NFS_MOUNT_NOAC)
		sb_mntdata.mntflags |= MS_SYNCHRONOUS;

	/* Get a superblock - note that we may end up sharing one that already exists */
	s = sget(fs_type, compare_super, nfs_set_super, &sb_mntdata);
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
		nfs_fill_super(s, data);
		nfs_fscache_get_super_cookie(
			s, data ? data->fscache_uniq : NULL, NULL);
	}

	mntroot = nfs_get_root(s, mntfh);
	if (IS_ERR(mntroot)) {
		error = PTR_ERR(mntroot);
		goto error_splat_super;
	}

	error = security_sb_set_mnt_opts(s, &data->lsm_opts);
	if (error)
		goto error_splat_root;

	s->s_flags |= MS_ACTIVE;
	mnt->mnt_sb = s;
	mnt->mnt_root = mntroot;
	error = 0;

out:
	nfs_free_parsed_mount_data(data);
	nfs_free_fhandle(mntfh);
	return error;

out_err_nosb:
	nfs_free_server(server);
	goto out;

error_splat_root:
	dput(mntroot);
error_splat_super:
	if (server && !s->s_root)
		bdi_unregister(&server->backing_dev_info);
error_splat_bdi:
	deactivate_locked_super(s);
	goto out;
}