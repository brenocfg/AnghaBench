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
struct cm4000_dev {scalar_t__ monitor_running; int /*<<< orphan*/  timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  devq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (int,struct cm4000_dev*,char*) ; 
 int /*<<< orphan*/  LOCK_MONITOR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void terminate_monitor(struct cm4000_dev *dev)
{

	/* tell the monitor to stop and wait until
	 * it terminates.
	 */
	DEBUGP(3, dev, "-> terminate_monitor\n");
	wait_event_interruptible(dev->devq,
				 test_and_set_bit(LOCK_MONITOR,
						  (void *)&dev->flags));

	/* now, LOCK_MONITOR has been set.
	 * allow a last cycle in the monitor.
	 * the monitor will indicate that it has
	 * finished by clearing this bit.
	 */
	DEBUGP(5, dev, "Now allow last cycle of monitor!\n");
	while (test_bit(LOCK_MONITOR, (void *)&dev->flags))
		msleep(25);

	DEBUGP(5, dev, "Delete timer\n");
	del_timer_sync(&dev->timer);
#ifdef PCMCIA_DEBUG
	dev->monitor_running = 0;
#endif

	DEBUGP(3, dev, "<- terminate_monitor\n");
}