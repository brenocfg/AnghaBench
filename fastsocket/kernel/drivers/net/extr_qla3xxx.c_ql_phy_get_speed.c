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
typedef  int u16 ;
struct ql3_adapter {int phyType; } ;

/* Variables and functions */
 int AUX_CONTROL_STATUS ; 
#define  PHY_AGERE_ET1011C 128 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int /*<<< orphan*/  ql_mii_read_reg (struct ql3_adapter*,int,int*) ; 

__attribute__((used)) static int ql_phy_get_speed(struct ql3_adapter *qdev)
{
	u16 reg;

	switch(qdev->phyType) {
	case PHY_AGERE_ET1011C:
	{
		if (ql_mii_read_reg(qdev, 0x1A, &reg) < 0)
			return 0;

		reg = (reg >> 8) & 3;
		break;
	}
	default:
	if (ql_mii_read_reg(qdev, AUX_CONTROL_STATUS, &reg) < 0)
		return 0;

	reg = (((reg & 0x18) >> 3) & 3);
	}

	switch(reg) {
		case 2:
		return SPEED_1000;
		case 1:
		return SPEED_100;
		case 0:
		return SPEED_10;
		default:
		return -1;
	}
}