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

/* Variables and functions */
 scalar_t__ IS_A_TT () ; 
 int /*<<< orphan*/  falcon_fairness_wait ; 
 int falcon_got_lock ; 
 int /*<<< orphan*/  falcon_try_wait ; 
 int falcon_trying_lock ; 
 scalar_t__ in_irq () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  scsi_falcon_intr ; 
 int /*<<< orphan*/  sleep_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdma_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stdma_others_waiting () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void falcon_get_lock(void)
{
	unsigned long flags;

	if (IS_A_TT())
		return;

	local_irq_save(flags);

	while (!in_irq() && falcon_got_lock && stdma_others_waiting())
		sleep_on(&falcon_fairness_wait);

	while (!falcon_got_lock) {
		if (in_irq())
			panic("Falcon SCSI hasn't ST-DMA lock in interrupt");
		if (!falcon_trying_lock) {
			falcon_trying_lock = 1;
			stdma_lock(scsi_falcon_intr, NULL);
			falcon_got_lock = 1;
			falcon_trying_lock = 0;
			wake_up(&falcon_try_wait);
		} else {
			sleep_on(&falcon_try_wait);
		}
	}

	local_irq_restore(flags);
	if (!falcon_got_lock)
		panic("Falcon SCSI: someone stole the lock :-(\n");
}