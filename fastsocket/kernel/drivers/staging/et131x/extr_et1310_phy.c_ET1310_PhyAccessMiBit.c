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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MiRead (struct et131x_adapter*,int,int*) ; 
 int /*<<< orphan*/  MiWrite (struct et131x_adapter*,int,int) ; 
#define  TRUEPHY_BIT_CLEAR 130 
#define  TRUEPHY_BIT_READ 129 
#define  TRUEPHY_BIT_SET 128 

void ET1310_PhyAccessMiBit(struct et131x_adapter *etdev, uint16_t action,
			   uint16_t regnum, uint16_t bitnum, uint8_t *value)
{
	uint16_t reg;
	uint16_t mask = 0;

	/* Create a mask to isolate the requested bit */
	mask = 0x0001 << bitnum;

	/* Read the requested register */
	MiRead(etdev, regnum, &reg);

	switch (action) {
	case TRUEPHY_BIT_READ:
		if (value != NULL)
			*value = (reg & mask) >> bitnum;
		break;

	case TRUEPHY_BIT_SET:
		reg |= mask;
		MiWrite(etdev, regnum, reg);
		break;

	case TRUEPHY_BIT_CLEAR:
		reg &= ~mask;
		MiWrite(etdev, regnum, reg);
		break;

	default:
		break;
	}
}