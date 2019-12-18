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
struct btrfs_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_dev_stat_set (struct btrfs_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btrfs_dev_stat_reset(struct btrfs_device *dev,
					int index)
{
	btrfs_dev_stat_set(dev, index, 0);
}