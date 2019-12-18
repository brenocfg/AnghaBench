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
struct NCR5380_hostdata {int /*<<< orphan*/  connected; int /*<<< orphan*/  issue_queue; int /*<<< orphan*/  disconnected_queue; } ;

/* Variables and functions */
 scalar_t__ IS_A_TT () ; 
 scalar_t__ falcon_dont_release ; 
 int /*<<< orphan*/  falcon_fairness_wait ; 
 scalar_t__ falcon_got_lock ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stdma_release () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void falcon_release_lock_if_possible(struct NCR5380_hostdata *hostdata)
{
	unsigned long flags;

	if (IS_A_TT())
		return;

	local_irq_save(flags);

	if (falcon_got_lock && !hostdata->disconnected_queue &&
	    !hostdata->issue_queue && !hostdata->connected) {

		if (falcon_dont_release) {
#if 0
			printk("WARNING: Lock release not allowed. Ignored\n");
#endif
			local_irq_restore(flags);
			return;
		}
		falcon_got_lock = 0;
		stdma_release();
		wake_up(&falcon_fairness_wait);
	}

	local_irq_restore(flags);
}