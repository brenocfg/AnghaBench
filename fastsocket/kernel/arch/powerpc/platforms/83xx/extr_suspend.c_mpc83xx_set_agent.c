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
struct TYPE_2__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  config1; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCCR1_USE_STATE ; 
 int /*<<< orphan*/  PMCER_PMCI ; 
 int /*<<< orphan*/  agent_thread_fn ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* pmc_regs ; 

__attribute__((used)) static void mpc83xx_set_agent(void)
{
	out_be32(&pmc_regs->config1, PMCCR1_USE_STATE);
	out_be32(&pmc_regs->mask, PMCER_PMCI);

	kthread_run(agent_thread_fn, NULL, "PCI power mgt");
}