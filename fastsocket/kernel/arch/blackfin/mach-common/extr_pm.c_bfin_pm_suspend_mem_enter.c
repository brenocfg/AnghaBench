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
 int ENOMEM ; 
 int FREQ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPWE ; 
 scalar_t__ L1_CODE_LENGTH ; 
 scalar_t__ L1_DATA_A_LENGTH ; 
 scalar_t__ L1_DATA_B_LENGTH ; 
 scalar_t__ L1_SCRATCH_LENGTH ; 
 int PHYWE ; 
 int SCKELOW ; 
 int /*<<< orphan*/  _disable_dcplb () ; 
 int /*<<< orphan*/  _disable_icplb () ; 
 int /*<<< orphan*/  _enable_dcplb () ; 
 int /*<<< orphan*/  _enable_icplb () ; 
 int /*<<< orphan*/  bf53x_resume_l1_mem (unsigned char*) ; 
 int /*<<< orphan*/  bf53x_suspend_l1_mem (unsigned char*) ; 
 int /*<<< orphan*/  bfin_gpio_pm_hibernate_restore () ; 
 int /*<<< orphan*/  bfin_gpio_pm_hibernate_suspend () ; 
 int bfin_read_VR_CTL () ; 
 int /*<<< orphan*/  blackfin_dma_resume () ; 
 int blackfin_dma_suspend () ; 
 int /*<<< orphan*/  do_hibernate (int) ; 
 int /*<<< orphan*/  flushinv_all_dcache () ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore_hw (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save_hw (unsigned long) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vr_wakeup ; 

int bfin_pm_suspend_mem_enter(void)
{
	unsigned long flags;
	int wakeup, ret;

	unsigned char *memptr = kmalloc(L1_CODE_LENGTH + L1_DATA_A_LENGTH
					 + L1_DATA_B_LENGTH + L1_SCRATCH_LENGTH,
					  GFP_KERNEL);

	if (memptr == NULL) {
		panic("bf53x_suspend_l1_mem malloc failed");
		return -ENOMEM;
	}

	wakeup = bfin_read_VR_CTL() & ~FREQ;
	wakeup |= SCKELOW;

#ifdef CONFIG_PM_BFIN_WAKE_PH6
	wakeup |= PHYWE;
#endif
#ifdef CONFIG_PM_BFIN_WAKE_GP
	wakeup |= GPWE;
#endif

	local_irq_save_hw(flags);

	ret = blackfin_dma_suspend();

	if (ret) {
		local_irq_restore_hw(flags);
		kfree(memptr);
		return ret;
	}

	bfin_gpio_pm_hibernate_suspend();

#if defined(CONFIG_BFIN_EXTMEM_WRITEBACK) || defined(CONFIG_BFIN_L2_WRITEBACK)
	flushinv_all_dcache();
#endif
	_disable_dcplb();
	_disable_icplb();
	bf53x_suspend_l1_mem(memptr);

	do_hibernate(wakeup | vr_wakeup);	/* Goodbye */

	bf53x_resume_l1_mem(memptr);

	_enable_icplb();
	_enable_dcplb();

	bfin_gpio_pm_hibernate_restore();
	blackfin_dma_resume();

	local_irq_restore_hw(flags);
	kfree(memptr);

	return 0;
}