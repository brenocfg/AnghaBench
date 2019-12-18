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
struct isci_host {TYPE_1__* smu_registers; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IHOST_IRQ_ENABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void sci_controller_disable_interrupts(struct isci_host *ihost)
{
	clear_bit(IHOST_IRQ_ENABLED, &ihost->flags);
	writel(0xffffffff, &ihost->smu_registers->interrupt_mask);
	readl(&ihost->smu_registers->interrupt_mask); /* flush */
}