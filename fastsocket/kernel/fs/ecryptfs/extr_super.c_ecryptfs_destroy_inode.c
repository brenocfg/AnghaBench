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
struct inode {int dummy; } ;
struct ecryptfs_inode_info {int /*<<< orphan*/  crypt_stat; TYPE_1__* lower_file; } ;
struct dentry {scalar_t__ d_inode; } ;
struct TYPE_2__ {struct dentry* f_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ecryptfs_destroy_crypt_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecryptfs_inode_info_cache ; 
 struct ecryptfs_inode_info* ecryptfs_inode_to_private (struct inode*) ; 
 int /*<<< orphan*/  fput (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ecryptfs_inode_info*) ; 

__attribute__((used)) static void ecryptfs_destroy_inode(struct inode *inode)
{
	struct ecryptfs_inode_info *inode_info;

	inode_info = ecryptfs_inode_to_private(inode);
	if (inode_info->lower_file) {
		struct dentry *lower_dentry =
			inode_info->lower_file->f_dentry;

		BUG_ON(!lower_dentry);
		if (lower_dentry->d_inode) {
			fput(inode_info->lower_file);
			inode_info->lower_file = NULL;
		}
	}
	ecryptfs_destroy_crypt_stat(&inode_info->crypt_stat);
	kmem_cache_free(ecryptfs_inode_info_cache, inode_info);
}