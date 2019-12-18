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
struct mpconf {TYPE_1__* multipaths; } ;
struct mddev {int raid_disks; struct mpconf* private; } ;
struct md_rdev {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int bdi_congested (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mddev_congested (struct mddev*,int) ; 
 struct md_rdev* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int multipath_congested(void *data, int bits)
{
	struct mddev *mddev = data;
	struct mpconf *conf = mddev->private;
	int i, ret = 0;

	if (mddev_congested(mddev, bits))
		return 1;

	rcu_read_lock();
	for (i = 0; i < mddev->raid_disks ; i++) {
		struct md_rdev *rdev = rcu_dereference(conf->multipaths[i].rdev);
		if (rdev && !test_bit(Faulty, &rdev->flags)) {
			struct request_queue *q = bdev_get_queue(rdev->bdev);

			ret |= bdi_congested(&q->backing_dev_info, bits);
			/* Just like multipath_map, we just check the
			 * first available device
			 */
			break;
		}
	}
	rcu_read_unlock();
	return ret;
}