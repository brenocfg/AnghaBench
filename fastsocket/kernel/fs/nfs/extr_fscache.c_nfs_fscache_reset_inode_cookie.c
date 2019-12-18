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
struct nfs_server {TYPE_1__* nfs_client; } ;
struct nfs_inode {struct fscache_cookie* fscache; } ;
struct inode {int dummy; } ;
struct fscache_cookie {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct nfs_server*,struct nfs_inode*,struct fscache_cookie*,struct fscache_cookie*) ; 
 struct fscache_cookie* fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_inode*) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (struct fscache_cookie*,int) ; 
 int /*<<< orphan*/  nfs_fscache_inode_lock (struct inode*) ; 
 int /*<<< orphan*/  nfs_fscache_inode_object_def ; 
 int /*<<< orphan*/  nfs_fscache_inode_unlock (struct inode*) ; 

void nfs_fscache_reset_inode_cookie(struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_server *nfss = NFS_SERVER(inode);
	struct fscache_cookie *old = nfsi->fscache;

	nfs_fscache_inode_lock(inode);
	if (nfsi->fscache) {
		/* retire the current fscache cache and get a new one */
		fscache_relinquish_cookie(nfsi->fscache, 1);

		nfsi->fscache = fscache_acquire_cookie(
			nfss->nfs_client->fscache,
			&nfs_fscache_inode_object_def,
			nfsi);

		dfprintk(FSCACHE,
			 "NFS: revalidation new cookie (0x%p/0x%p/0x%p/0x%p)\n",
			 nfss, nfsi, old, nfsi->fscache);
	}
	nfs_fscache_inode_unlock(inode);
}