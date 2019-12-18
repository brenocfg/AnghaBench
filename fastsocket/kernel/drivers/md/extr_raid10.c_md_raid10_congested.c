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
struct request_queue {int /*<<< orphan*/  backing_dev_info; } ;
struct TYPE_5__ {int raid_disks; } ;
struct TYPE_4__ {int raid_disks; } ;
struct r10conf {scalar_t__ pending_count; TYPE_3__* mirrors; TYPE_2__ prev; TYPE_1__ geo; } ;
struct mddev {struct r10conf* private; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int BDI_async_congested ; 
 int /*<<< orphan*/  Faulty ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int bdi_congested (int /*<<< orphan*/ *,int) ; 
 scalar_t__ max_queued_requests ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int md_raid10_congested(struct mddev *mddev, int bits)
{
	struct r10conf *conf = mddev->private;
	int i, ret = 0;

	if ((bits & (1 << BDI_async_congested)) &&
	    conf->pending_count >= max_queued_requests)
		return 1;

	rcu_read_lock();
	for (i = 0;
	     (i < conf->geo.raid_disks || i < conf->prev.raid_disks)
		     && ret == 0;
	     i++) {
		struct md_rdev *rdev = rcu_dereference(conf->mirrors[i].rdev);
		if (rdev && !test_bit(Faulty, &rdev->flags)) {
			struct request_queue *q = bdev_get_queue(rdev->bdev);

			ret |= bdi_congested(&q->backing_dev_info, bits);
		}
	}
	rcu_read_unlock();
	return ret;
}