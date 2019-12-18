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
 int CB1_INT ; 
 size_t IFR ; 
 int /*<<< orphan*/  IRQ_MAC_ADB_CL ; 
 int /*<<< orphan*/  IRQ_MAC_ADB_SR ; 
 int SR_INT ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pmu_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* via1 ; 

void 
pmu_poll(void)
{
	unsigned long flags;

	local_irq_save(flags);
	if (via1[IFR] & SR_INT) {
		via1[IFR] = SR_INT;
		pmu_interrupt(IRQ_MAC_ADB_SR, NULL);
	}
	if (via1[IFR] & CB1_INT) {
		via1[IFR] = CB1_INT;
		pmu_interrupt(IRQ_MAC_ADB_CL, NULL);
	}
	local_irq_restore(flags);
}