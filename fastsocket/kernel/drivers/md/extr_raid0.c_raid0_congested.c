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
struct request_queue {int /*<<< orphan*/  backing_dev_info; } ;
struct r0conf {TYPE_1__* strip_zone; struct md_rdev** devlist; } ;
struct mddev {struct r0conf* private; } ;
struct md_rdev {int /*<<< orphan*/  bdev; } ;
struct TYPE_2__ {int nb_dev; } ;

/* Variables and functions */
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int bdi_congested (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mddev_congested (struct mddev*,int) ; 

__attribute__((used)) static int raid0_congested(void *data, int bits)
{
	struct mddev *mddev = data;
	struct r0conf *conf = mddev->private;
	struct md_rdev **devlist = conf->devlist;
	int raid_disks = conf->strip_zone[0].nb_dev;
	int i, ret = 0;

	if (mddev_congested(mddev, bits))
		return 1;

	for (i = 0; i < raid_disks && !ret ; i++) {
		struct request_queue *q = bdev_get_queue(devlist[i]->bdev);

		ret |= bdi_congested(&q->backing_dev_info, bits);
	}
	return ret;
}