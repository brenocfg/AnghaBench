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
 scalar_t__ ANOMALY_05000435 ; 
 int /*<<< orphan*/  CONFIG_PM_WAKEUP_GPIO_NUMBER ; 
 int IWR_DISABLE_ALL ; 
 int IWR_ENABLE (int) ; 
 int /*<<< orphan*/  WAKEUP_TYPE ; 
 int /*<<< orphan*/  bfin_pm_standby_restore () ; 
 int /*<<< orphan*/  bfin_pm_standby_setup () ; 
 int /*<<< orphan*/ * bfin_sic_iwr ; 
 int /*<<< orphan*/  bfin_write_SIC_IWR (int) ; 
 int /*<<< orphan*/  bfin_write_SIC_IWR0 (int) ; 
 int /*<<< orphan*/  bfin_write_SIC_IWR1 (int) ; 
 int /*<<< orphan*/  bfin_write_SIC_IWR2 (int) ; 
 int /*<<< orphan*/  gpio_pm_wakeup_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore_hw (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save_hw (unsigned long) ; 
 int /*<<< orphan*/  sleep_deeper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bfin_pm_suspend_standby_enter(void)
{
	unsigned long flags;

#ifdef CONFIG_PM_WAKEUP_BY_GPIO
	gpio_pm_wakeup_request(CONFIG_PM_WAKEUP_GPIO_NUMBER, WAKEUP_TYPE);
#endif

	local_irq_save_hw(flags);
	bfin_pm_standby_setup();

#ifdef CONFIG_PM_BFIN_SLEEP_DEEPER
	sleep_deeper(bfin_sic_iwr[0], bfin_sic_iwr[1], bfin_sic_iwr[2]);
#else
	sleep_mode(bfin_sic_iwr[0], bfin_sic_iwr[1], bfin_sic_iwr[2]);
#endif

	bfin_pm_standby_restore();

#ifdef SIC_IWR0
	bfin_write_SIC_IWR0(IWR_DISABLE_ALL);
# ifdef SIC_IWR1
	/* BF52x system reset does not properly reset SIC_IWR1 which
	 * will screw up the bootrom as it relies on MDMA0/1 waking it
	 * up from IDLE instructions.  See this report for more info:
	 * http://blackfin.uclinux.org/gf/tracker/4323
	 */
	if (ANOMALY_05000435)
		bfin_write_SIC_IWR1(IWR_ENABLE(10) | IWR_ENABLE(11));
	else
		bfin_write_SIC_IWR1(IWR_DISABLE_ALL);
# endif
# ifdef SIC_IWR2
	bfin_write_SIC_IWR2(IWR_DISABLE_ALL);
# endif
#else
	bfin_write_SIC_IWR(IWR_DISABLE_ALL);
#endif

	local_irq_restore_hw(flags);
}