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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_HT_BBCFG ; 
 int B43_PHY_HT_BBCFG_RSTCCA ; 
 int /*<<< orphan*/  B43_PHY_HT_RF_SEQ_TRIG_RST2RX ; 
 int /*<<< orphan*/  b43_phy_force_clock (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_ht_force_rf_sequence (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_phy_ht_reset_cca(struct b43_wldev *dev)
{
	u16 bbcfg;

	b43_phy_force_clock(dev, true);
	bbcfg = b43_phy_read(dev, B43_PHY_HT_BBCFG);
	b43_phy_write(dev, B43_PHY_HT_BBCFG, bbcfg | B43_PHY_HT_BBCFG_RSTCCA);
	udelay(1);
	b43_phy_write(dev, B43_PHY_HT_BBCFG, bbcfg & ~B43_PHY_HT_BBCFG_RSTCCA);
	b43_phy_force_clock(dev, false);

	b43_phy_ht_force_rf_sequence(dev, B43_PHY_HT_RF_SEQ_TRIG_RST2RX);
}