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
 int /*<<< orphan*/  btrfs_dev_stat_inc (struct btrfs_device*,int) ; 
 int /*<<< orphan*/  btrfs_dev_stat_print_on_error (struct btrfs_device*) ; 

void btrfs_dev_stat_inc_and_print(struct btrfs_device *dev, int index)
{
	btrfs_dev_stat_inc(dev, index);
	btrfs_dev_stat_print_on_error(dev);
}