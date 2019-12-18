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
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_pu (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void wlc_lcnphy_crsuprs(struct brcms_phy *pi, int channel)
{
	u16 afectrlovr, afectrlovrval;
	afectrlovr = read_phy_reg(pi, 0x43b);
	afectrlovrval = read_phy_reg(pi, 0x43c);
	if (channel != 0) {
		mod_phy_reg(pi, 0x43b, (0x1 << 1), (1) << 1);

		mod_phy_reg(pi, 0x43c, (0x1 << 1), (0) << 1);

		mod_phy_reg(pi, 0x43b, (0x1 << 4), (1) << 4);

		mod_phy_reg(pi, 0x43c, (0x1 << 6), (0) << 6);

		write_phy_reg(pi, 0x44b, 0xffff);
		wlc_lcnphy_tx_pu(pi, 1);

		mod_phy_reg(pi, 0x634, (0xff << 8), (0) << 8);

		or_phy_reg(pi, 0x6da, 0x0080);

		or_phy_reg(pi, 0x00a, 0x228);
	} else {
		and_phy_reg(pi, 0x00a, ~(0x228));

		and_phy_reg(pi, 0x6da, 0xFF7F);
		write_phy_reg(pi, 0x43b, afectrlovr);
		write_phy_reg(pi, 0x43c, afectrlovrval);
	}
}