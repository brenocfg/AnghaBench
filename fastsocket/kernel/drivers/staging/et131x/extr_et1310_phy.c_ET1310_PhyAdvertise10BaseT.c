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
 int /*<<< orphan*/  PHY_AUTO_ADVERTISEMENT ; 
#define  TRUEPHY_ADV_DUPLEX_BOTH 131 
#define  TRUEPHY_ADV_DUPLEX_FULL 130 
#define  TRUEPHY_ADV_DUPLEX_HALF 129 
#define  TRUEPHY_ADV_DUPLEX_NONE 128 

void ET1310_PhyAdvertise10BaseT(struct et131x_adapter *etdev,
				uint16_t duplex)
{
	uint16_t data;

	/* Read the Autonegotiation Register (10/100) */
	MiRead(etdev, PHY_AUTO_ADVERTISEMENT, &data);

	/* Clear bits 5,6 */
	data &= ~0x0060;

	switch (duplex) {
	case TRUEPHY_ADV_DUPLEX_NONE:
		/* Duplex already cleared, do nothing */
		break;

	case TRUEPHY_ADV_DUPLEX_FULL:
		/* Set Bit 6 */
		data |= 0x0040;
		break;

	case TRUEPHY_ADV_DUPLEX_HALF:
		/* Set Bit 5 */
		data |= 0x0020;
		break;

	case TRUEPHY_ADV_DUPLEX_BOTH:
	default:
		/* Set Bits 5,6 */
		data |= 0x0060;
		break;
	}

	/* Write back advertisement */
	MiWrite(etdev, PHY_AUTO_ADVERTISEMENT, data);
}