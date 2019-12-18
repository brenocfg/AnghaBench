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

/* Variables and functions */
 scalar_t__ btrfs_free_space_cachep ; 
 scalar_t__ btrfs_inode_cachep ; 
 scalar_t__ btrfs_path_cachep ; 
 scalar_t__ btrfs_trans_handle_cachep ; 
 scalar_t__ btrfs_transaction_cachep ; 
 int /*<<< orphan*/  kmem_cache_destroy (scalar_t__) ; 

void btrfs_destroy_cachep(void)
{
	if (btrfs_inode_cachep)
		kmem_cache_destroy(btrfs_inode_cachep);
	if (btrfs_trans_handle_cachep)
		kmem_cache_destroy(btrfs_trans_handle_cachep);
	if (btrfs_transaction_cachep)
		kmem_cache_destroy(btrfs_transaction_cachep);
	if (btrfs_path_cachep)
		kmem_cache_destroy(btrfs_path_cachep);
	if (btrfs_free_space_cachep)
		kmem_cache_destroy(btrfs_free_space_cachep);
}