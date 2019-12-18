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
 int /*<<< orphan*/  ADB_DELAY ; 
 size_t IFR ; 
 int SR_INT ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  maciisi_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int* via ; 

void
maciisi_poll(void)
{
	unsigned long flags;

	local_irq_save(flags);
	if (via[IFR] & SR_INT) {
		maciisi_interrupt(0, NULL);
	}
	else /* avoid calling this function too quickly in a loop */
		udelay(ADB_DELAY);

	local_irq_restore(flags);
}