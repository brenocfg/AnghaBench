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
struct lcnphy_txgains {int dac_gain; int gm_gain; int pga_gain; int pad_gain; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int read_phy_reg (struct brcms_phy*,int) ; 

__attribute__((used)) static void
wlc_lcnphy_get_tx_gain(struct brcms_phy *pi, struct lcnphy_txgains *gains)
{
	u16 dac_gain, rfgain0, rfgain1;

	dac_gain = read_phy_reg(pi, 0x439) >> 0;
	gains->dac_gain = (dac_gain & 0x380) >> 7;

	rfgain0 = (read_phy_reg(pi, 0x4b5) & (0xffff << 0)) >> 0;
	rfgain1 = (read_phy_reg(pi, 0x4fb) & (0x7fff << 0)) >> 0;

	gains->gm_gain = rfgain0 & 0xff;
	gains->pga_gain = (rfgain0 >> 8) & 0xff;
	gains->pad_gain = rfgain1 & 0xff;
}