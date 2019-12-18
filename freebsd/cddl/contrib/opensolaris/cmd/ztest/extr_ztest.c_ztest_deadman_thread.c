#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int zs_thread_stop; int zs_thread_start; } ;
typedef  TYPE_1__ ztest_shared_t ;
struct TYPE_6__ {int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int hrtime_t ;

/* Variables and functions */
 int MSEC2NSEC (int) ; 
 scalar_t__ NSEC2MSEC (int) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ spa_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_deadman (int /*<<< orphan*/ *) ; 
 int zfs_deadman_synctime_ms ; 
 TYPE_2__* ztest_spa ; 

__attribute__((used)) static void *
ztest_deadman_thread(void *arg)
{
	ztest_shared_t *zs = arg;
	spa_t *spa = ztest_spa;
	hrtime_t delta, total = 0;

	for (;;) {
		delta = zs->zs_thread_stop - zs->zs_thread_start +
		    MSEC2NSEC(zfs_deadman_synctime_ms);

		(void) poll(NULL, 0, (int)NSEC2MSEC(delta));

		/*
		 * If the pool is suspended then fail immediately. Otherwise,
		 * check to see if the pool is making any progress. If
		 * vdev_deadman() discovers that there hasn't been any recent
		 * I/Os then it will end up aborting the tests.
		 */
		if (spa_suspended(spa) || spa->spa_root_vdev == NULL) {
			fatal(0, "aborting test after %llu seconds because "
			    "pool has transitioned to a suspended state.",
			    zfs_deadman_synctime_ms / 1000);
			return (NULL);
		}
		vdev_deadman(spa->spa_root_vdev);

		total += zfs_deadman_synctime_ms/1000;
		(void) printf("ztest has been running for %lld seconds\n",
		    total);
	}
}