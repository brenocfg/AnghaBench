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
struct btrfs_device {scalar_t__ dev_stat_values; } ;

/* Variables and functions */
 int atomic_read (scalar_t__) ; 

__attribute__((used)) static inline int btrfs_dev_stat_read(struct btrfs_device *dev,
				      int index)
{
	return atomic_read(dev->dev_stat_values + index);
}