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
 int GFER ; 
 int GRER ; 
 int PCFR ; 
 int PCFR_FP ; 
 int PCFR_FS ; 
 int PCFR_OPDE ; 
 int /*<<< orphan*/  PMCR ; 
 int /*<<< orphan*/  PMCR_SF ; 
 scalar_t__ PSPR ; 
 int PWER ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void sa1100_power_off(void)
{
	mdelay(100);
	local_irq_disable();
	/* disable internal oscillator, float CS lines */
	PCFR = (PCFR_OPDE | PCFR_FP | PCFR_FS);
	/* enable wake-up on GPIO0 (Assabet...) */
	PWER = GFER = GRER = 1;
	/*
	 * set scratchpad to zero, just in case it is used as a
	 * restart address by the bootloader.
	 */
	PSPR = 0;
	/* enter sleep mode */
	PMCR = PMCR_SF;
}