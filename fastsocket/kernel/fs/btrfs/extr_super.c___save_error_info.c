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
struct btrfs_fs_info {int /*<<< orphan*/  fs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SUPER_FLAG_ERROR ; 

__attribute__((used)) static void __save_error_info(struct btrfs_fs_info *fs_info)
{
	/*
	 * today we only save the error info into ram.  Long term we'll
	 * also send it down to the disk
	 */
	fs_info->fs_state = BTRFS_SUPER_FLAG_ERROR;
}