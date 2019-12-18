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
struct et131x_adapter {int /*<<< orphan*/  Flags; TYPE_1__ PoMgmt; int /*<<< orphan*/  AiForceDpx; int /*<<< orphan*/  AiForceSpeed; TYPE_3__* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  pm_csr; } ;
struct TYPE_6__ {TYPE_2__ global; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_PMCSR_INIT ; 
 int /*<<< orphan*/  ET_PM_PHY_SW_COMA ; 
 int /*<<< orphan*/  et131x_adapter_setup (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_init_send (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_reset_recv (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_rx_dma_enable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_soft_reset (struct et131x_adapter*) ; 
 int /*<<< orphan*/  fMP_ADAPTER_LOWER_POWER ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void DisablePhyComa(struct et131x_adapter *etdev)
{
	u32 GlobalPmCSR;

	GlobalPmCSR = readl(&etdev->regs->global.pm_csr);

	/* Disable phy_sw_coma register and re-enable JAGCore clocks */
	GlobalPmCSR |= ET_PMCSR_INIT;
	GlobalPmCSR &= ~ET_PM_PHY_SW_COMA;
	writel(GlobalPmCSR, &etdev->regs->global.pm_csr);

	/* Restore the GbE PHY speed and duplex modes;
	 * Reset JAGCore; re-configure and initialize JAGCore and gigE PHY
	 */
	etdev->AiForceSpeed = etdev->PoMgmt.PowerDownSpeed;
	etdev->AiForceDpx = etdev->PoMgmt.PowerDownDuplex;

	/* Re-initialize the send structures */
	et131x_init_send(etdev);

	/* Reset the RFD list and re-start RU  */
	et131x_reset_recv(etdev);

	/* Bring the device back to the state it was during init prior to
	 * autonegotiation being complete.  This way, when we get the auto-neg
	 * complete interrupt, we can complete init by calling ConfigMacREGS2.
	 */
	et131x_soft_reset(etdev);

	/* setup et1310 as per the documentation ?? */
	et131x_adapter_setup(etdev);

	/* Allow Tx to restart */
	etdev->Flags &= ~fMP_ADAPTER_LOWER_POWER;

	/* Need to re-enable Rx. */
	et131x_rx_dma_enable(etdev);
}