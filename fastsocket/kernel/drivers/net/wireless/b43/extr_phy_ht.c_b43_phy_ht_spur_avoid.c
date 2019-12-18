#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ieee80211_channel {int hw_value; } ;
struct bcma_device {TYPE_1__* bus; } ;
struct b43_wldev {TYPE_2__* dev; } ;
struct TYPE_4__ {struct bcma_device* bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  drv_cc; } ;

/* Variables and functions */
 int B43_BCMA_CLKCTLST_80211_PLL_REQ ; 
 int B43_BCMA_CLKCTLST_80211_PLL_ST ; 
 int B43_BCMA_CLKCTLST_PHY_PLL_REQ ; 
 int B43_BCMA_CLKCTLST_PHY_PLL_ST ; 
 int /*<<< orphan*/  B43_MMIO_TSF_CLK_FRAC_HIGH ; 
 int /*<<< orphan*/  B43_MMIO_TSF_CLK_FRAC_LOW ; 
 int /*<<< orphan*/  B43_PHY_HT_BBCFG ; 
 int B43_PHY_HT_BBCFG_RSTRX ; 
 int /*<<< orphan*/  b43_phy_ht_reset_cca (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_core_pll_ctl (struct bcma_device*,int,int,int) ; 
 int /*<<< orphan*/  bcma_pmu_spuravoid_pllupdate (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void b43_phy_ht_spur_avoid(struct b43_wldev *dev,
				  struct ieee80211_channel *new_channel)
{
	struct bcma_device *core = dev->dev->bdev;
	int spuravoid = 0;
	u16 tmp;

	/* Check for 13 and 14 is just a guess, we don't have enough logs. */
	if (new_channel->hw_value == 13 || new_channel->hw_value == 14)
		spuravoid = 1;
	bcma_core_pll_ctl(core, B43_BCMA_CLKCTLST_PHY_PLL_REQ, 0, false);
	bcma_pmu_spuravoid_pllupdate(&core->bus->drv_cc, spuravoid);
	bcma_core_pll_ctl(core,
			  B43_BCMA_CLKCTLST_80211_PLL_REQ |
			  B43_BCMA_CLKCTLST_PHY_PLL_REQ,
			  B43_BCMA_CLKCTLST_80211_PLL_ST |
			  B43_BCMA_CLKCTLST_PHY_PLL_ST, false);

	/* Values has been taken from wlc_bmac_switch_macfreq comments */
	switch (spuravoid) {
	case 2: /* 126MHz */
		tmp = 0x2082;
		break;
	case 1: /* 123MHz */
		tmp = 0x5341;
		break;
	default: /* 120MHz */
		tmp = 0x8889;
	}

	b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_LOW, tmp);
	b43_write16(dev, B43_MMIO_TSF_CLK_FRAC_HIGH, 0x8);

	/* TODO: reset PLL */

	if (spuravoid)
		b43_phy_set(dev, B43_PHY_HT_BBCFG, B43_PHY_HT_BBCFG_RSTRX);
	else
		b43_phy_mask(dev, B43_PHY_HT_BBCFG,
				~B43_PHY_HT_BBCFG_RSTRX & 0xFFFF);

	b43_phy_ht_reset_cca(dev);
}