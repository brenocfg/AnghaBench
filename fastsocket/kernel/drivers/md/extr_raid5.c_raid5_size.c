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
struct r5conf {int max_degraded; int /*<<< orphan*/  previous_raid_disks; int /*<<< orphan*/  raid_disks; } ;
struct mddev {int dev_sectors; scalar_t__ new_chunk_sectors; scalar_t__ chunk_sectors; struct r5conf* private; } ;
typedef  int sector_t ;

/* Variables and functions */
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t
raid5_size(struct mddev *mddev, sector_t sectors, int raid_disks)
{
	struct r5conf *conf = mddev->private;

	if (!sectors)
		sectors = mddev->dev_sectors;
	if (!raid_disks)
		/* size is defined by the smallest of previous and new size */
		raid_disks = min(conf->raid_disks, conf->previous_raid_disks);

	sectors &= ~((sector_t)mddev->chunk_sectors - 1);
	sectors &= ~((sector_t)mddev->new_chunk_sectors - 1);
	return sectors * (raid_disks - conf->max_degraded);
}