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
struct btrfs_fs_info {int /*<<< orphan*/  balance_cancel_req; int /*<<< orphan*/  balance_pause_req; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int balance_need_close(struct btrfs_fs_info *fs_info)
{
	/* cancel requested || normal exit path */
	return atomic_read(&fs_info->balance_cancel_req) ||
		(atomic_read(&fs_info->balance_pause_req) == 0 &&
		 atomic_read(&fs_info->balance_cancel_req) == 0);
}