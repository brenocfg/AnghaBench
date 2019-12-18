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
struct inode {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_DATA ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int __nfs_revalidate_inode (int /*<<< orphan*/ ,struct inode*) ; 
 int nfs_invalidate_mapping (struct inode*,struct address_space*) ; 
 scalar_t__ nfs_mapping_need_revalidate_inode (struct inode*) ; 

int nfs_revalidate_mapping(struct inode *inode, struct address_space *mapping)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	int ret = 0;

	if (nfs_mapping_need_revalidate_inode(inode)) {
		ret = __nfs_revalidate_inode(NFS_SERVER(inode), inode);
		if (ret < 0)
			goto out;
	}
	if (nfsi->cache_validity & NFS_INO_INVALID_DATA)
		ret = nfs_invalidate_mapping(inode, mapping);
out:
	return ret;
}