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
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_IDLECT1 ; 
 int /*<<< orphan*/  ARM_IDLECT2 ; 
 int OMAP1510_BIG_SLEEP_REQUEST ; 
 int OMAP1610_IDLECT1_SLEEP_VAL ; 
 scalar_t__ cpu_is_omap15xx () ; 
 scalar_t__ enable_dyn_sleep ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_fiq_enable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ need_resched () ; 
 int omap_dm_timer_modify_idlect_mask (int) ; 
 scalar_t__ omap_dma_running () ; 
 int omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_sram_suspend (int,int) ; 
 int /*<<< orphan*/  omap_writel (int,int /*<<< orphan*/ ) ; 

void omap1_pm_idle(void)
{
	extern __u32 arm_idlect1_mask;
	__u32 use_idlect1 = arm_idlect1_mask;
	int do_sleep = 0;

	local_irq_disable();
	local_fiq_disable();
	if (need_resched()) {
		local_fiq_enable();
		local_irq_enable();
		return;
	}

#ifdef CONFIG_OMAP_MPU_TIMER
#warning Enable 32kHz OS timer in order to allow sleep states in idle
	use_idlect1 = use_idlect1 & ~(1 << 9);
#else

	while (enable_dyn_sleep) {

#ifdef CONFIG_CBUS_TAHVO_USB
		extern int vbus_active;
		/* Clock requirements? */
		if (vbus_active)
			break;
#endif
		do_sleep = 1;
		break;
	}

#endif

#ifdef CONFIG_OMAP_DM_TIMER
	use_idlect1 = omap_dm_timer_modify_idlect_mask(use_idlect1);
#endif

	if (omap_dma_running())
		use_idlect1 &= ~(1 << 6);

	/* We should be able to remove the do_sleep variable and multiple
	 * tests above as soon as drivers, timer and DMA code have been fixed.
	 * Even the sleep block count should become obsolete. */
	if ((use_idlect1 != ~0) || !do_sleep) {

		__u32 saved_idlect1 = omap_readl(ARM_IDLECT1);
		if (cpu_is_omap15xx())
			use_idlect1 &= OMAP1510_BIG_SLEEP_REQUEST;
		else
			use_idlect1 &= OMAP1610_IDLECT1_SLEEP_VAL;
		omap_writel(use_idlect1, ARM_IDLECT1);
		__asm__ volatile ("mcr	p15, 0, r0, c7, c0, 4");
		omap_writel(saved_idlect1, ARM_IDLECT1);

		local_fiq_enable();
		local_irq_enable();
		return;
	}
	omap_sram_suspend(omap_readl(ARM_IDLECT1),
			  omap_readl(ARM_IDLECT2));

	local_fiq_enable();
	local_irq_enable();
}