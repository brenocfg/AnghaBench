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
typedef  int suspend_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_AIC_IMR ; 
 int /*<<< orphan*/  AT91_AIC_IPR ; 
 int AT91_ID_FIQ ; 
 int AT91_ID_SYS ; 
 int /*<<< orphan*/  AT91_PMC_PCSR ; 
#define  PM_SUSPEND_MEM 130 
#define  PM_SUSPEND_ON 129 
#define  PM_SUSPEND_STANDBY 128 
 int at91_extern_irq ; 
 int /*<<< orphan*/  at91_gpio_resume () ; 
 int /*<<< orphan*/  at91_gpio_suspend () ; 
 int /*<<< orphan*/  at91_irq_resume () ; 
 int /*<<< orphan*/  at91_irq_suspend () ; 
 int /*<<< orphan*/  at91_pm_verify_clocks () ; 
 int /*<<< orphan*/  at91_slow_clock ; 
 int /*<<< orphan*/  at91_slow_clock_sz ; 
 int at91_sys_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  (*) (),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  sdram_selfrefresh_disable () ; 
 int /*<<< orphan*/  sdram_selfrefresh_enable () ; 
 int /*<<< orphan*/  slow_clock () ; 
 int target_state ; 

__attribute__((used)) static int at91_pm_enter(suspend_state_t state)
{
	at91_gpio_suspend();
	at91_irq_suspend();

	pr_debug("AT91: PM - wake mask %08x, pm state %d\n",
			/* remember all the always-wake irqs */
			(at91_sys_read(AT91_PMC_PCSR)
					| (1 << AT91_ID_FIQ)
					| (1 << AT91_ID_SYS)
					| (at91_extern_irq))
				& at91_sys_read(AT91_AIC_IMR),
			state);

	switch (state) {
		/*
		 * Suspend-to-RAM is like STANDBY plus slow clock mode, so
		 * drivers must suspend more deeply:  only the master clock
		 * controller may be using the main oscillator.
		 */
		case PM_SUSPEND_MEM:
			/*
			 * Ensure that clocks are in a valid state.
			 */
			if (!at91_pm_verify_clocks())
				goto error;

			/*
			 * Enter slow clock mode by switching over to clk32k and
			 * turning off the main oscillator; reverse on wakeup.
			 */
			if (slow_clock) {
#ifdef CONFIG_AT91_SLOW_CLOCK
				/* copy slow_clock handler to SRAM, and call it */
				memcpy(slow_clock, at91_slow_clock, at91_slow_clock_sz);
#endif
				slow_clock();
				break;
			} else {
				pr_info("AT91: PM - no slow clock mode enabled ...\n");
				/* FALLTHROUGH leaving master clock alone */
			}

		/*
		 * STANDBY mode has *all* drivers suspended; ignores irqs not
		 * marked as 'wakeup' event sources; and reduces DRAM power.
		 * But otherwise it's identical to PM_SUSPEND_ON:  cpu idle, and
		 * nothing fancy done with main or cpu clocks.
		 */
		case PM_SUSPEND_STANDBY:
			/*
			 * NOTE: the Wait-for-Interrupt instruction needs to be
			 * in icache so no SDRAM accesses are needed until the
			 * wakeup IRQ occurs and self-refresh is terminated.
			 */
			asm("b 1f; .align 5; 1:");
			asm("mcr p15, 0, r0, c7, c10, 4");	/* drain write buffer */
			sdram_selfrefresh_enable();
			asm("mcr p15, 0, r0, c7, c0, 4");	/* wait for interrupt */
			sdram_selfrefresh_disable();
			break;

		case PM_SUSPEND_ON:
			asm("mcr p15, 0, r0, c7, c0, 4");	/* wait for interrupt */
			break;

		default:
			pr_debug("AT91: PM - bogus suspend state %d\n", state);
			goto error;
	}

	pr_debug("AT91: PM - wakeup %08x\n",
			at91_sys_read(AT91_AIC_IPR) & at91_sys_read(AT91_AIC_IMR));

error:
	target_state = PM_SUSPEND_ON;
	at91_irq_resume();
	at91_gpio_resume();
	return 0;
}