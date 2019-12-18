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
 int /*<<< orphan*/  LUBBOCK_SD_IRQ ; 
 int LUB_IRQ_SET_CLR ; 
 scalar_t__ MMC_POLL_RATE ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mmc_detect_int (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mmc_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void lubbock_mmc_poll(unsigned long data)
{
	unsigned long flags;

	/* clear any previous irq state, then ... */
	local_irq_save(flags);
	LUB_IRQ_SET_CLR &= ~(1 << 0);
	local_irq_restore(flags);

	/* poll until mmc/sd card is removed */
	if (LUB_IRQ_SET_CLR & (1 << 0))
		mod_timer(&mmc_timer, jiffies + MMC_POLL_RATE);
	else {
		(void) mmc_detect_int(LUBBOCK_SD_IRQ, (void *)data);
		enable_irq(LUBBOCK_SD_IRQ);
	}
}