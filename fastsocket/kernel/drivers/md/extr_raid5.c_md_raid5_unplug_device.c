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
struct r5conf {TYPE_1__* mddev; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  seq_flush; int /*<<< orphan*/  plug; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ plugger_remove_plug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raid5_activate_delayed (struct r5conf*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unplug_slaves (TYPE_1__*) ; 

void md_raid5_unplug_device(struct r5conf *conf)
{
	unsigned long flags;

	spin_lock_irqsave(&conf->device_lock, flags);

	if (plugger_remove_plug(&conf->plug)) {
		conf->seq_flush++;
		raid5_activate_delayed(conf);
	}
	md_wakeup_thread(conf->mddev->thread);

	spin_unlock_irqrestore(&conf->device_lock, flags);

	unplug_slaves(conf->mddev);
}