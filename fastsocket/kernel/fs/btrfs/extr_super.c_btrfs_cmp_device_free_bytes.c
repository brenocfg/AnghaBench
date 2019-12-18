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
struct btrfs_device_info {scalar_t__ max_avail; } ;

/* Variables and functions */

__attribute__((used)) static int btrfs_cmp_device_free_bytes(const void *dev_info1,
				       const void *dev_info2)
{
	if (((struct btrfs_device_info *)dev_info1)->max_avail >
	    ((struct btrfs_device_info *)dev_info2)->max_avail)
		return -1;
	else if (((struct btrfs_device_info *)dev_info1)->max_avail <
		 ((struct btrfs_device_info *)dev_info2)->max_avail)
		return 1;
	else
	return 0;
}