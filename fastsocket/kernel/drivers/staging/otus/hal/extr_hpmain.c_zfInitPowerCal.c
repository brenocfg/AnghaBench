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
typedef  int /*<<< orphan*/  zdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  zm_write_phy_reg (int,int) ; 

void zfInitPowerCal(zdev_t* dev)
{
    //Program PHY Tx power relatives registers
#define zm_write_phy_reg(cr, val) reg_write((cr*4)+0x9800, val)

    zm_write_phy_reg(79, 0x7f);
    zm_write_phy_reg(77, 0x3f3f3f3f);
    zm_write_phy_reg(78, 0x3f3f3f3f);
    zm_write_phy_reg(653, 0x3f3f3f3f);
    zm_write_phy_reg(654, 0x3f3f3f3f);
    zm_write_phy_reg(739, 0x3f3f3f3f);
    zm_write_phy_reg(740, 0x3f3f3f3f);
    zm_write_phy_reg(755, 0x3f3f3f3f);
    zm_write_phy_reg(756, 0x3f3f3f3f);
    zm_write_phy_reg(757, 0x3f3f3f3f);

#undef zm_write_phy_reg
}