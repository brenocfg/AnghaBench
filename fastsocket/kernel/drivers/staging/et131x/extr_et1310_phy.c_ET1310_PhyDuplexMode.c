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
typedef  scalar_t__ uint16_t ;
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MiRead (struct et131x_adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  MiWrite (struct et131x_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 scalar_t__ TRUEPHY_DUPLEX_FULL ; 

void ET1310_PhyDuplexMode(struct et131x_adapter *etdev, uint16_t duplex)
{
	uint16_t data;

	MiRead(etdev, PHY_CONTROL, &data);

	if (duplex == TRUEPHY_DUPLEX_FULL) {
		/* Set Full Duplex */
		data |= 0x100;
		MiWrite(etdev, PHY_CONTROL, data);
	} else {
		/* Set Half Duplex */
		data &= ~0x100;
		MiWrite(etdev, PHY_CONTROL, data);
	}
}