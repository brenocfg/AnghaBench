#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ supports_gmii; } ;
struct rtl8169_private {scalar_t__ mac_version; TYPE_1__ mii; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 int MII_ADVERTISE ; 
 int MII_BMCR ; 
 int MII_CTRL1000 ; 
 scalar_t__ RTL_GIGA_MAC_VER_02 ; 
 scalar_t__ RTL_GIGA_MAC_VER_03 ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  link ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct rtl8169_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int rtl_readphy (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static int rtl8169_set_speed_xmii(struct net_device *dev,
				  u8 autoneg, u16 speed, u8 duplex, u32 adv)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	int giga_ctrl, bmcr;
	int rc = -EINVAL;

	rtl_writephy(tp, 0x1f, 0x0000);

	if (autoneg == AUTONEG_ENABLE) {
		int auto_nego;

		auto_nego = rtl_readphy(tp, MII_ADVERTISE);
		auto_nego &= ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
				ADVERTISE_100HALF | ADVERTISE_100FULL);

		if (adv & ADVERTISED_10baseT_Half)
			auto_nego |= ADVERTISE_10HALF;
		if (adv & ADVERTISED_10baseT_Full)
			auto_nego |= ADVERTISE_10FULL;
		if (adv & ADVERTISED_100baseT_Half)
			auto_nego |= ADVERTISE_100HALF;
		if (adv & ADVERTISED_100baseT_Full)
			auto_nego |= ADVERTISE_100FULL;

		auto_nego |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;

		giga_ctrl = rtl_readphy(tp, MII_CTRL1000);
		giga_ctrl &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);

		/* The 8100e/8101e/8102e do Fast Ethernet only. */
		if (tp->mii.supports_gmii) {
			if (adv & ADVERTISED_1000baseT_Half)
				giga_ctrl |= ADVERTISE_1000HALF;
			if (adv & ADVERTISED_1000baseT_Full)
				giga_ctrl |= ADVERTISE_1000FULL;
		} else if (adv & (ADVERTISED_1000baseT_Half |
				  ADVERTISED_1000baseT_Full)) {
			netif_info(tp, link, dev,
				   "PHY does not support 1000Mbps\n");
			goto out;
		}

		bmcr = BMCR_ANENABLE | BMCR_ANRESTART;

		rtl_writephy(tp, MII_ADVERTISE, auto_nego);
		rtl_writephy(tp, MII_CTRL1000, giga_ctrl);
	} else {
		giga_ctrl = 0;

		if (speed == SPEED_10)
			bmcr = 0;
		else if (speed == SPEED_100)
			bmcr = BMCR_SPEED100;
		else
			goto out;

		if (duplex == DUPLEX_FULL)
			bmcr |= BMCR_FULLDPLX;
	}

	rtl_writephy(tp, MII_BMCR, bmcr);

	if (tp->mac_version == RTL_GIGA_MAC_VER_02 ||
	    tp->mac_version == RTL_GIGA_MAC_VER_03) {
		if ((speed == SPEED_100) && (autoneg != AUTONEG_ENABLE)) {
			rtl_writephy(tp, 0x17, 0x2138);
			rtl_writephy(tp, 0x0e, 0x0260);
		} else {
			rtl_writephy(tp, 0x17, 0x2108);
			rtl_writephy(tp, 0x0e, 0x0000);
		}
	}

	rc = 0;
out:
	return rc;
}