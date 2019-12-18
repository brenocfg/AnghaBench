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
typedef  int uint16_t ;
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MiRead (struct et131x_adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  MiWrite (struct et131x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
#define  TRUEPHY_SPEED_1000MBPS 130 
#define  TRUEPHY_SPEED_100MBPS 129 
#define  TRUEPHY_SPEED_10MBPS 128 

void ET1310_PhySpeedSelect(struct et131x_adapter *etdev, uint16_t speed)
{
	uint16_t data;

	/* Read the PHY control register */
	MiRead(etdev, PHY_CONTROL, &data);

	/* Clear all Speed settings (Bits 6, 13) */
	data &= ~0x2040;

	/* Reset the speed bits based on user selection */
	switch (speed) {
	case TRUEPHY_SPEED_10MBPS:
		/* Bits already cleared above, do nothing */
		break;

	case TRUEPHY_SPEED_100MBPS:
		/* 100M == Set bit 13 */
		data |= 0x2000;
		break;

	case TRUEPHY_SPEED_1000MBPS:
	default:
		data |= 0x0040;
		break;
	}

	/* Write back the new speed */
	MiWrite(etdev, PHY_CONTROL, data);
}