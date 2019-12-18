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
struct r1conf {scalar_t__ barrier; int /*<<< orphan*/  resync_lock; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  nr_waiting; } ;

/* Variables and functions */
 scalar_t__ RESYNC_DEPTH ; 
 int /*<<< orphan*/  md_raid1_unplug_device (struct r1conf*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raise_barrier(struct r1conf *conf)
{
	spin_lock_irq(&conf->resync_lock);

	/* Wait until no block IO is waiting */
	wait_event_lock_irq(conf->wait_barrier, !conf->nr_waiting,
			    conf->resync_lock,
			    md_raid1_unplug_device(conf));

	/* block any new IO from starting */
	conf->barrier++;

	/* Now wait for all pending IO to complete */
	wait_event_lock_irq(conf->wait_barrier,
			    !conf->nr_pending && conf->barrier < RESYNC_DEPTH,
			    conf->resync_lock,
			    md_raid1_unplug_device(conf));

	spin_unlock_irq(&conf->resync_lock);
}