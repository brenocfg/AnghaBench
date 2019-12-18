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
struct rpc_cred {int dummy; } ;
struct nfs_access_entry {int mask; int /*<<< orphan*/  jiffies; struct rpc_cred* cred; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int (* access ) (struct inode*,struct nfs_access_entry*) ;} ;

/* Variables and functions */
 int EACCES ; 
 int ESTALE ; 
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_STALE ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nfs_access_add_cache (struct inode*,struct nfs_access_entry*) ; 
 int nfs_access_get_cached (struct inode*,struct rpc_cred*,struct nfs_access_entry*) ; 
 int /*<<< orphan*/  nfs_zap_caches (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct inode*,struct nfs_access_entry*) ; 

__attribute__((used)) static int nfs_do_access(struct inode *inode, struct rpc_cred *cred, int mask)
{
	struct nfs_access_entry cache;
	int status;

	status = nfs_access_get_cached(inode, cred, &cache);
	if (status == 0)
		goto out;

	/* Be clever: ask server to check for all possible rights */
	cache.mask = MAY_EXEC | MAY_WRITE | MAY_READ;
	cache.cred = cred;
	cache.jiffies = jiffies;
	status = NFS_PROTO(inode)->access(inode, &cache);
	if (status != 0) {
		if (status == -ESTALE) {
			nfs_zap_caches(inode);
			if (!S_ISDIR(inode->i_mode))
				set_bit(NFS_INO_STALE, &NFS_I(inode)->flags);
		}
		return status;
	}
	nfs_access_add_cache(inode, &cache);
out:
	if ((mask & ~cache.mask & (MAY_READ | MAY_WRITE | MAY_EXEC)) == 0)
		return 0;
	return -EACCES;
}