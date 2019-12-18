#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int raid_devs; } ;
struct raid_set {TYPE_1__ set; struct raid_dev* dev; } ;
struct raid_dev {TYPE_2__* dev; } ;
struct TYPE_6__ {scalar_t__ bd_dev; } ;
struct TYPE_5__ {TYPE_3__* bdev; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int raid_dev_lookup(struct raid_set *rs, struct raid_dev *dev_lookup)
{
	unsigned p;
	struct raid_dev *dev;

	/*
	 * Must be an incremental loop, because the device array
	 * can have empty slots still on calls from raid_ctr()
	 */
	for (dev = rs->dev, p = 0;
	     dev->dev && p < rs->set.raid_devs;
	     dev++, p++) {
		if (dev_lookup->dev->bdev->bd_dev == dev->dev->bdev->bd_dev)
			return p;
	}

	return -ENODEV;
}