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
typedef  int u32 ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_MOD ; 
 unsigned long long NSEC_PER_USEC ; 
 int /*<<< orphan*/  OCP_MOD ; 
 int /*<<< orphan*/  OMAP24XX_PM_WKST2 ; 
 int OMAP24XX_USBSTANDBYCTRL ; 
 int /*<<< orphan*/  OMAP2_CONTROL_DEVCONF0 ; 
 int /*<<< orphan*/  OMAP2_PRCM_IRQSTATUS_MPU_OFFSET ; 
 int /*<<< orphan*/  OMAP_SDRC_REGADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_WKST ; 
 int /*<<< orphan*/  PM_WKST1 ; 
 int /*<<< orphan*/  PWRDM_POWER_RET ; 
 int /*<<< orphan*/  SDRC_DLLA_CTRL ; 
 int /*<<< orphan*/  SDRC_POWER ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getnstimeofday (struct timespec*) ; 
 int /*<<< orphan*/  mpu_pwrdm ; 
 int /*<<< orphan*/  omap2_gpio_prepare_for_retention () ; 
 int /*<<< orphan*/  omap2_gpio_resume_after_retention () ; 
 scalar_t__ omap2_pm_debug ; 
 int /*<<< orphan*/  omap2_pm_dump (int /*<<< orphan*/ ,int,unsigned long long) ; 
 int /*<<< orphan*/  omap2_sram_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_ctrl_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ctrl_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ omap_irq_pending () ; 
 int /*<<< orphan*/  omap_uart_prepare_idle (int) ; 
 int /*<<< orphan*/  omap_uart_resume_idle (int) ; 
 int /*<<< orphan*/  osc_ck ; 
 int /*<<< orphan*/  prm_clear_mod_reg_bits (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int prm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prm_write_mod_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_set_logic_retst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwrdm_set_next_pwrst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdrc_read_reg (int /*<<< orphan*/ ) ; 
 struct timespec timespec_sub (struct timespec,struct timespec) ; 
 unsigned long long timespec_to_ns (struct timespec*) ; 

__attribute__((used)) static void omap2_enter_full_retention(void)
{
	u32 l;
	struct timespec ts_preidle, ts_postidle, ts_idle;

	/* There is 1 reference hold for all children of the oscillator
	 * clock, the following will remove it. If no one else uses the
	 * oscillator itself it will be disabled if/when we enter retention
	 * mode.
	 */
	clk_disable(osc_ck);

	/* Clear old wake-up events */
	/* REVISIT: These write to reserved bits? */
	prm_write_mod_reg(0xffffffff, CORE_MOD, PM_WKST1);
	prm_write_mod_reg(0xffffffff, CORE_MOD, OMAP24XX_PM_WKST2);
	prm_write_mod_reg(0xffffffff, WKUP_MOD, PM_WKST);

	/*
	 * Set MPU powerdomain's next power state to RETENTION;
	 * preserve logic state during retention
	 */
	pwrdm_set_logic_retst(mpu_pwrdm, PWRDM_POWER_RET);
	pwrdm_set_next_pwrst(mpu_pwrdm, PWRDM_POWER_RET);

	/* Workaround to kill USB */
	l = omap_ctrl_readl(OMAP2_CONTROL_DEVCONF0) | OMAP24XX_USBSTANDBYCTRL;
	omap_ctrl_writel(l, OMAP2_CONTROL_DEVCONF0);

	omap2_gpio_prepare_for_retention();

	if (omap2_pm_debug) {
		omap2_pm_dump(0, 0, 0);
		getnstimeofday(&ts_preidle);
	}

	/* One last check for pending IRQs to avoid extra latency due
	 * to sleeping unnecessarily. */
	if (omap_irq_pending())
		goto no_sleep;

	omap_uart_prepare_idle(0);
	omap_uart_prepare_idle(1);
	omap_uart_prepare_idle(2);

	/* Jump to SRAM suspend code */
	omap2_sram_suspend(sdrc_read_reg(SDRC_DLLA_CTRL),
			   OMAP_SDRC_REGADDR(SDRC_DLLA_CTRL),
			   OMAP_SDRC_REGADDR(SDRC_POWER));

	omap_uart_resume_idle(2);
	omap_uart_resume_idle(1);
	omap_uart_resume_idle(0);

no_sleep:
	if (omap2_pm_debug) {
		unsigned long long tmp;

		getnstimeofday(&ts_postidle);
		ts_idle = timespec_sub(ts_postidle, ts_preidle);
		tmp = timespec_to_ns(&ts_idle) * NSEC_PER_USEC;
		omap2_pm_dump(0, 1, tmp);
	}
	omap2_gpio_resume_after_retention();

	clk_enable(osc_ck);

	/* clear CORE wake-up events */
	prm_write_mod_reg(0xffffffff, CORE_MOD, PM_WKST1);
	prm_write_mod_reg(0xffffffff, CORE_MOD, OMAP24XX_PM_WKST2);

	/* wakeup domain events - bit 1: GPT1, bit5 GPIO */
	prm_clear_mod_reg_bits(0x4 | 0x1, WKUP_MOD, PM_WKST);

	/* MPU domain wake events */
	l = prm_read_mod_reg(OCP_MOD, OMAP2_PRCM_IRQSTATUS_MPU_OFFSET);
	if (l & 0x01)
		prm_write_mod_reg(0x01, OCP_MOD,
				  OMAP2_PRCM_IRQSTATUS_MPU_OFFSET);
	if (l & 0x20)
		prm_write_mod_reg(0x20, OCP_MOD,
				  OMAP2_PRCM_IRQSTATUS_MPU_OFFSET);

	/* Mask future PRCM-to-MPU interrupts */
	prm_write_mod_reg(0x0, OCP_MOD, OMAP2_PRCM_IRQSTATUS_MPU_OFFSET);
}