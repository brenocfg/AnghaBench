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
struct nfs_inode {int cache_validity; scalar_t__ change_attr; } ;
struct nfs4_change_info {scalar_t__ before; scalar_t__ after; int /*<<< orphan*/  atomic; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ATTR ; 
 int NFS_INO_INVALID_DATA ; 
 int NFS_INO_REVAL_PAGECACHE ; 
 int /*<<< orphan*/  nfs_force_lookup_revalidate (struct inode*) ; 
 int /*<<< orphan*/  nfs_fscache_invalidate (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_changeattr(struct inode *dir, struct nfs4_change_info *cinfo)
{
	struct nfs_inode *nfsi = NFS_I(dir);

	spin_lock(&dir->i_lock);
	nfsi->cache_validity |= NFS_INO_INVALID_ATTR|NFS_INO_REVAL_PAGECACHE|NFS_INO_INVALID_DATA;
	if (!cinfo->atomic || cinfo->before != nfsi->change_attr)
		nfs_force_lookup_revalidate(dir);
	nfsi->change_attr = cinfo->after;
	nfs_fscache_invalidate(dir);
	spin_unlock(&dir->i_lock);
}