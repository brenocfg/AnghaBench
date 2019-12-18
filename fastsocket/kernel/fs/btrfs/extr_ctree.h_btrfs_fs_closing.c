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
struct btrfs_fs_info {int closing; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static inline int btrfs_fs_closing(struct btrfs_fs_info *fs_info)
{
	/*
	 * Get synced with close_ctree()
	 */
	smp_mb();
	return fs_info->closing;
}