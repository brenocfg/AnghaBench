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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  config1; } ;

/* Variables and functions */
 int PMCCR1_CURR_STATE ; 
 int PMCCR1_NEXT_STATE ; 
 int PMCCR1_NEXT_STATE_SHIFT ; 
 int /*<<< orphan*/  agent_wq ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_pci_agent ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int pci_pm_state ; 
 TYPE_1__* pmc_regs ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpc83xx_change_state(void)
{
	u32 curr_state;
	u32 reg_cfg1 = in_be32(&pmc_regs->config1);

	if (is_pci_agent) {
		pci_pm_state = (reg_cfg1 & PMCCR1_NEXT_STATE) >>
		               PMCCR1_NEXT_STATE_SHIFT;
		curr_state = reg_cfg1 & PMCCR1_CURR_STATE;

		if (curr_state != pci_pm_state) {
			reg_cfg1 &= ~PMCCR1_CURR_STATE;
			reg_cfg1 |= pci_pm_state;
			out_be32(&pmc_regs->config1, reg_cfg1);

			wake_up(&agent_wq);
			return 1;
		}
	}

	return 0;
}