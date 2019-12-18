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
struct nfs_server {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int cache_validity; } ;

/* Variables and functions */
 int ESTALE ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ATTR ; 
 scalar_t__ NFS_STALE (struct inode*) ; 
 int __nfs_revalidate_inode (struct nfs_server*,struct inode*) ; 
 int /*<<< orphan*/  nfs_attribute_cache_expired (struct inode*) ; 

int nfs_revalidate_inode(struct nfs_server *server, struct inode *inode)
{
	if (!(NFS_I(inode)->cache_validity & NFS_INO_INVALID_ATTR)
			&& !nfs_attribute_cache_expired(inode))
		return NFS_STALE(inode) ? -ESTALE : 0;
	return __nfs_revalidate_inode(server, inode);
}