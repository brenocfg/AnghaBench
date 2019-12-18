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
struct btrfs_free_space_ctl {int dummy; } ;
struct btrfs_free_space {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool pinned_use_bitmap(struct btrfs_free_space_ctl *ctl,
			      struct btrfs_free_space *info)
{
	/*
	 * We always use extents for two reasons:
	 *
	 * - The pinned tree is only used during the process of caching
	 *   work.
	 * - Make code simpler. See btrfs_unpin_free_ino().
	 */
	return false;
}