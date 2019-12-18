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
struct ecryptfs_sb_info {int /*<<< orphan*/  mount_crypt_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecryptfs_destroy_mount_crypt_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecryptfs_sb_info_cache ; 
 int /*<<< orphan*/  ecryptfs_set_superblock_private (struct super_block*,int /*<<< orphan*/ *) ; 
 struct ecryptfs_sb_info* ecryptfs_superblock_to_private (struct super_block*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ecryptfs_sb_info*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void ecryptfs_put_super(struct super_block *sb)
{
	struct ecryptfs_sb_info *sb_info = ecryptfs_superblock_to_private(sb);

	lock_kernel();

	ecryptfs_destroy_mount_crypt_stat(&sb_info->mount_crypt_stat);
	kmem_cache_free(ecryptfs_sb_info_cache, sb_info);
	ecryptfs_set_superblock_private(sb, NULL);

	unlock_kernel();
}