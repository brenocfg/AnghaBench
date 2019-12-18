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
struct nfs_inode {int cache_validity; } ;
struct nfs_fattr {int valid; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int NFS_ATTR_FATTR ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ATTR ; 
 int NFS_INO_INVALID_DATA ; 
 int NFS_INO_REVAL_PAGECACHE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fscache_invalidate (struct inode*) ; 
 int nfs_refresh_inode_locked (struct inode*,struct nfs_fattr*) ; 

__attribute__((used)) static int nfs_post_op_update_inode_locked(struct inode *inode, struct nfs_fattr *fattr)
{
	struct nfs_inode *nfsi = NFS_I(inode);

	nfsi->cache_validity |= NFS_INO_INVALID_ATTR|NFS_INO_REVAL_PAGECACHE;
	if (S_ISDIR(inode->i_mode)) {
		nfsi->cache_validity |= NFS_INO_INVALID_DATA;
		nfs_fscache_invalidate(inode);
	}
	if ((fattr->valid & NFS_ATTR_FATTR) == 0)
		return 0;
	return nfs_refresh_inode_locked(inode, fattr);
}