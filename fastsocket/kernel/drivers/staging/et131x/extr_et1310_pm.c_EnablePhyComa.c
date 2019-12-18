#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  PowerDownDuplex; int /*<<< orphan*/  PowerDownSpeed; } ;
struct et131x_adapter {TYPE_3__* regs; int /*<<< orphan*/  SendHWLock; int /*<<< orphan*/  Flags; int /*<<< orphan*/  AiForceDpx; TYPE_1__ PoMgmt; int /*<<< orphan*/  AiForceSpeed; } ;
struct TYPE_5__ {int /*<<< orphan*/  pm_csr; } ;
struct TYPE_6__ {TYPE_2__ global; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_PMCSR_INIT ; 
 int /*<<< orphan*/  ET_PM_PHY_SW_COMA ; 
 int /*<<< orphan*/  fMP_ADAPTER_LOWER_POWER ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void EnablePhyComa(struct et131x_adapter *etdev)
{
	unsigned long flags;
	u32 GlobalPmCSR;

	GlobalPmCSR = readl(&etdev->regs->global.pm_csr);

	/* Save the GbE PHY speed and duplex modes. Need to restore this
	 * when cable is plugged back in
	 */
	etdev->PoMgmt.PowerDownSpeed = etdev->AiForceSpeed;
	etdev->PoMgmt.PowerDownDuplex = etdev->AiForceDpx;

	/* Stop sending packets. */
	spin_lock_irqsave(&etdev->SendHWLock, flags);
	etdev->Flags |= fMP_ADAPTER_LOWER_POWER;
	spin_unlock_irqrestore(&etdev->SendHWLock, flags);

	/* Wait for outstanding Receive packets */

	/* Gate off JAGCore 3 clock domains */
	GlobalPmCSR &= ~ET_PMCSR_INIT;
	writel(GlobalPmCSR, &etdev->regs->global.pm_csr);

	/* Program gigE PHY in to Coma mode */
	GlobalPmCSR |= ET_PM_PHY_SW_COMA;
	writel(GlobalPmCSR, &etdev->regs->global.pm_csr);
}