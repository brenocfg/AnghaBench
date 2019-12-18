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
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET1310_PhyAdvertise1000BaseT (struct et131x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET1310_PhyAdvertise100BaseT (struct et131x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET1310_PhyAdvertise10BaseT (struct et131x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET1310_PhyPowerDown (struct et131x_adapter*,int) ; 
 int /*<<< orphan*/  TRUEPHY_ADV_DUPLEX_FULL ; 
 int /*<<< orphan*/  TRUEPHY_ADV_DUPLEX_NONE ; 

void TPAL_SetPhy100FullDuplex(struct et131x_adapter *etdev)
{
	/* Power down PHY */
	ET1310_PhyPowerDown(etdev, 1);

	/* First we need to turn off all other advertisement */
	ET1310_PhyAdvertise1000BaseT(etdev, TRUEPHY_ADV_DUPLEX_NONE);

	ET1310_PhyAdvertise10BaseT(etdev, TRUEPHY_ADV_DUPLEX_NONE);

	/* Set our advertise values accordingly */
	ET1310_PhyAdvertise100BaseT(etdev, TRUEPHY_ADV_DUPLEX_FULL);

	/* Power up PHY */
	ET1310_PhyPowerDown(etdev, 0);
}