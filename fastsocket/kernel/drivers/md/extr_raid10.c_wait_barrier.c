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
struct r10conf {int /*<<< orphan*/  resync_lock; scalar_t__ nr_pending; int /*<<< orphan*/  nr_waiting; scalar_t__ barrier; int /*<<< orphan*/  wait_barrier; } ;
struct TYPE_2__ {scalar_t__ bio_tail; scalar_t__ bio_list; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  md_raid10_unplug_device (struct r10conf*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_barrier(struct r10conf *conf)
{
	spin_lock_irq(&conf->resync_lock);
	if (conf->barrier) {
		conf->nr_waiting++;
		/* Wait for the barrier to drop.
		 * However if there are already pending
		 * requests (preventing the barrier from
		 * rising completely), and the
		 * pre-process bio queue isn't empty,
		 * then don't wait, as we need to empty
		 * that queue to get the nr_pending
		 * count down.
		 */
		wait_event_lock_irq(conf->wait_barrier,
				    !conf->barrier ||
				    (conf->nr_pending &&
				     current->bio_list &&
				     current->bio_tail),
				    conf->resync_lock,
				    md_raid10_unplug_device(conf)
			);
		conf->nr_waiting--;
	}
	conf->nr_pending++;
	spin_unlock_irq(&conf->resync_lock);
}