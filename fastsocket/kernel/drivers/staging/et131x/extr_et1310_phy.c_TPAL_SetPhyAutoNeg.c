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
struct et131x_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET1310_PhyAdvertise1000BaseT (struct et131x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET1310_PhyAdvertise100BaseT (struct et131x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET1310_PhyAdvertise10BaseT (struct et131x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET1310_PhyAutoNeg (struct et131x_adapter*,int) ; 
 int /*<<< orphan*/  ET1310_PhyPowerDown (struct et131x_adapter*,int) ; 
 scalar_t__ ET131X_PCI_DEVICE_ID_FAST ; 
 int /*<<< orphan*/  TRUEPHY_ADV_DUPLEX_BOTH ; 
 int /*<<< orphan*/  TRUEPHY_ADV_DUPLEX_FULL ; 
 int /*<<< orphan*/  TRUEPHY_ADV_DUPLEX_NONE ; 

void TPAL_SetPhyAutoNeg(struct et131x_adapter *etdev)
{
	/* Power down PHY */
	ET1310_PhyPowerDown(etdev, 1);

	/* Turn on advertisement of all capabilities */
	ET1310_PhyAdvertise10BaseT(etdev, TRUEPHY_ADV_DUPLEX_BOTH);

	ET1310_PhyAdvertise100BaseT(etdev, TRUEPHY_ADV_DUPLEX_BOTH);

	if (etdev->pdev->device != ET131X_PCI_DEVICE_ID_FAST)
		ET1310_PhyAdvertise1000BaseT(etdev, TRUEPHY_ADV_DUPLEX_FULL);
	else
		ET1310_PhyAdvertise1000BaseT(etdev, TRUEPHY_ADV_DUPLEX_NONE);

	/* Make sure auto-neg is ON (it is disabled in FORCE modes) */
	ET1310_PhyAutoNeg(etdev, true);

	/* Power up PHY */
	ET1310_PhyPowerDown(etdev, 0);
}