#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int raid_devs; } ;
struct raid_set {struct raid_dev* dev; TYPE_1__ set; } ;
struct raid_dev {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 scalar_t__ TestClearDevIoQueued (struct raid_dev*) ; 
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_unplug (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_unplug(struct raid_set *rs)
{
	struct raid_dev *dev = rs->dev + rs->set.raid_devs;

	while (dev-- > rs->dev) {
		/* Only call any device unplug function, if io got queued. */
		if (TestClearDevIoQueued(dev))
			blk_unplug(bdev_get_queue(dev->dev->bdev));
	}
}