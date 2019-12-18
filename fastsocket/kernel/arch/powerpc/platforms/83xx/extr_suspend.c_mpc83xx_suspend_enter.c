#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  suspend_state_t ;
struct TYPE_2__ {int /*<<< orphan*/  config1; int /*<<< orphan*/  mask; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int EAGAIN ; 
 int PMCCR1_PME_EN ; 
 int PMCCR1_POWER_OFF ; 
 int PMCCR_DLPEN ; 
 int PMCCR_SLPEN ; 
 int PMCER_ALL ; 
 int PMCER_PMCI ; 
 scalar_t__ deep_sleeping ; 
 int /*<<< orphan*/  enable_kernel_fp () ; 
 int /*<<< orphan*/  immrbase ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc6xx_enter_standby () ; 
 int /*<<< orphan*/  mpc83xx_enter_deep_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int pci_pm_state ; 
 TYPE_1__* pmc_regs ; 
 scalar_t__ wake_from_pci ; 

__attribute__((used)) static int mpc83xx_suspend_enter(suspend_state_t state)
{
	int ret = -EAGAIN;

	/* Don't go to sleep if there's a race where pci_pm_state changes
	 * between the agent thread checking it and the PM code disabling
	 * interrupts.
	 */
	if (wake_from_pci) {
		if (pci_pm_state != (deep_sleeping ? 3 : 2))
			goto out;

		out_be32(&pmc_regs->config1,
		         in_be32(&pmc_regs->config1) | PMCCR1_PME_EN);
	}

	/* Put the system into low-power mode and the RAM
	 * into self-refresh mode once the core goes to
	 * sleep.
	 */

	out_be32(&pmc_regs->config, PMCCR_SLPEN | PMCCR_DLPEN);

	/* If it has deep sleep (i.e. it's an 831x or compatible),
	 * disable power to the core upon entering sleep mode.  This will
	 * require going through the boot firmware upon a wakeup event.
	 */

	if (deep_sleeping) {
		out_be32(&pmc_regs->mask, PMCER_ALL);

		out_be32(&pmc_regs->config1,
		         in_be32(&pmc_regs->config1) | PMCCR1_POWER_OFF);

		enable_kernel_fp();

		mpc83xx_enter_deep_sleep(immrbase);

		out_be32(&pmc_regs->config1,
		         in_be32(&pmc_regs->config1) & ~PMCCR1_POWER_OFF);

		out_be32(&pmc_regs->mask, PMCER_PMCI);
	} else {
		out_be32(&pmc_regs->mask, PMCER_PMCI);

		mpc6xx_enter_standby();
	}

	ret = 0;

out:
	out_be32(&pmc_regs->config1,
	         in_be32(&pmc_regs->config1) & ~PMCCR1_PME_EN);

	return ret;
}