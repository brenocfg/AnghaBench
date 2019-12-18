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
struct mv643xx_eth_shared_private {int /*<<< orphan*/  smi_busy_wait; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ERR_INT_CAUSE ; 
 int ERR_INT_SMI_DONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mv643xx_eth_err_irq(int irq, void *dev_id)
{
	struct mv643xx_eth_shared_private *msp = dev_id;

	if (readl(msp->base + ERR_INT_CAUSE) & ERR_INT_SMI_DONE) {
		writel(~ERR_INT_SMI_DONE, msp->base + ERR_INT_CAUSE);
		wake_up(&msp->smi_busy_wait);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}