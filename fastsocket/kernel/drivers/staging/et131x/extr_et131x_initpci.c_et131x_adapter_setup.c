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
struct et131x_adapter {TYPE_1__* pdev; TYPE_2__* regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  mmc_ctrl; } ;
struct TYPE_5__ {TYPE_3__ mmc; } ;
struct TYPE_4__ {scalar_t__ device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ConfigGlobalRegs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ConfigMACRegs1 (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ConfigMacStatRegs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ConfigRxDmaRegs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ConfigRxMacRegs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ConfigTxDmaRegs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ConfigTxMacRegs (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ET1310_PhyAdvertise1000BaseT (struct et131x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET1310_PhyInit (struct et131x_adapter*) ; 
 int /*<<< orphan*/  ET1310_PhyPowerDown (struct et131x_adapter*,int) ; 
 int /*<<< orphan*/  ET1310_PhyReset (struct et131x_adapter*) ; 
 scalar_t__ ET131X_PCI_DEVICE_ID_FAST ; 
 int /*<<< orphan*/  ET_MMC_ENABLE ; 
 int /*<<< orphan*/  TRUEPHY_ADV_DUPLEX_FULL ; 
 int /*<<< orphan*/  TRUEPHY_ADV_DUPLEX_NONE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  et131x_setphy_normal (struct et131x_adapter*) ; 
 int et131x_xcvr_find (struct et131x_adapter*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int et131x_adapter_setup(struct et131x_adapter *etdev)
{
	int status = 0;

	/* Configure the JAGCore */
	ConfigGlobalRegs(etdev);

	ConfigMACRegs1(etdev);

	/* Configure the MMC registers */
	/* All we need to do is initialize the Memory Control Register */
	writel(ET_MMC_ENABLE, &etdev->regs->mmc.mmc_ctrl);

	ConfigRxMacRegs(etdev);
	ConfigTxMacRegs(etdev);

	ConfigRxDmaRegs(etdev);
	ConfigTxDmaRegs(etdev);

	ConfigMacStatRegs(etdev);

	/* Move the following code to Timer function?? */
	status = et131x_xcvr_find(etdev);

	if (status != 0)
		dev_warn(&etdev->pdev->dev, "Could not find the xcvr\n");

	/* Prepare the TRUEPHY library. */
	ET1310_PhyInit(etdev);

	/* Reset the phy now so changes take place */
	ET1310_PhyReset(etdev);

	/* Power down PHY */
	ET1310_PhyPowerDown(etdev, 1);

	/*
	 * We need to turn off 1000 base half dulplex, the mac does not
	 * support it. For the 10/100 part, turn off all gig advertisement
	 */
	if (etdev->pdev->device != ET131X_PCI_DEVICE_ID_FAST)
		ET1310_PhyAdvertise1000BaseT(etdev, TRUEPHY_ADV_DUPLEX_FULL);
	else
		ET1310_PhyAdvertise1000BaseT(etdev, TRUEPHY_ADV_DUPLEX_NONE);

	/* Power up PHY */
	ET1310_PhyPowerDown(etdev, 0);

	et131x_setphy_normal(etdev);
;	return status;
}