#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int raid_devs; int /*<<< orphan*/  sectors_per_dev; } ;
struct raid_set {TYPE_1__ set; struct raid_dev* dev; } ;
struct raid_dev {int /*<<< orphan*/  start; int /*<<< orphan*/  dev; } ;
struct dm_target {struct raid_set* private; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */

__attribute__((used)) static int raid_iterate_devices(struct dm_target *ti,
				iterate_devices_callout_fn fn, void *data)
{
	int ret;
	struct raid_set *rs = ti->private;
	struct raid_dev *dev;
	sector_t sectors_per_dev = rs->set.sectors_per_dev;

	for (dev = rs->dev, ret = 0;
	     !ret && dev < rs->dev + rs->set.raid_devs; dev++)
		ret = fn(ti, dev->dev, dev->start, sectors_per_dev, data);

	return ret;
}