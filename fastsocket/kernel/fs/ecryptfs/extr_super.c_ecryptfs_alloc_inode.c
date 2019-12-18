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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct ecryptfs_inode_info {struct inode vfs_inode; int /*<<< orphan*/ * lower_file; int /*<<< orphan*/  lower_file_mutex; int /*<<< orphan*/  crypt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ecryptfs_init_crypt_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecryptfs_inode_info_cache ; 
 struct ecryptfs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct inode *ecryptfs_alloc_inode(struct super_block *sb)
{
	struct ecryptfs_inode_info *inode_info;
	struct inode *inode = NULL;

	inode_info = kmem_cache_alloc(ecryptfs_inode_info_cache, GFP_KERNEL);
	if (unlikely(!inode_info))
		goto out;
	ecryptfs_init_crypt_stat(&inode_info->crypt_stat);
	mutex_init(&inode_info->lower_file_mutex);
	inode_info->lower_file = NULL;
	inode = &inode_info->vfs_inode;
out:
	return inode;
}