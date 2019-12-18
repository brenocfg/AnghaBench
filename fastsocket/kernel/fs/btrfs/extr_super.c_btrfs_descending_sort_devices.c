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
struct btrfs_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_cmp_device_free_bytes ; 
 int /*<<< orphan*/  sort (struct btrfs_device_info*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void btrfs_descending_sort_devices(
					struct btrfs_device_info *devices,
					size_t nr_devices)
{
	sort(devices, nr_devices, sizeof(struct btrfs_device_info),
	     btrfs_cmp_device_free_bytes, NULL);
}