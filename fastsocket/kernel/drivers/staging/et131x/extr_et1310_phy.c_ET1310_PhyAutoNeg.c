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

void ET1310_PhyAutoNeg(struct et131x_adapter *etdev, bool enable)
{
	uint16_t data;

	MiRead(etdev, PHY_CONTROL, &data);

	if (enable == true) {
		/* Autonegotiation ON */
		data |= 0x1000;
		MiWrite(etdev, PHY_CONTROL, data);
	} else {
		/* Autonegotiation OFF */
		data &= ~0x1000;
		MiWrite(etdev, PHY_CONTROL, data);
	}
}