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
struct btrfs_fs_info {int /*<<< orphan*/  cleaner_mutex; int /*<<< orphan*/  transaction_kthread_mutex; } ;

/* Variables and functions */
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_freeze(struct super_block *sb)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(sb);
	mutex_lock(&fs_info->transaction_kthread_mutex);
	mutex_lock(&fs_info->cleaner_mutex);
	return 0;
}