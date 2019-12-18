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
struct btrfs_fs_info {int /*<<< orphan*/  transaction_kthread_mutex; int /*<<< orphan*/  cleaner_mutex; } ;

/* Variables and functions */
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_unfreeze(struct super_block *sb)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(sb);
	mutex_unlock(&fs_info->cleaner_mutex);
	mutex_unlock(&fs_info->transaction_kthread_mutex);
	return 0;
}