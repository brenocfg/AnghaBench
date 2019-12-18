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
struct r8180_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ IEEE_A ; 
 int RF_PARA ; 
 int RF_TIMING ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl8225z2_set_gain (struct net_device*,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_rtl8225 (struct net_device*,int,int) ; 

void rtl8225z2_rf_set_mode(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	if (priv->ieee80211->mode == IEEE_A) {
		write_rtl8225(dev, 0x5, 0x1865);
		write_nic_dword(dev, RF_PARA, 0x10084);
		write_nic_dword(dev, RF_TIMING, 0xa8008);
		write_phy_ofdm(dev, 0x0, 0x0);
		write_phy_ofdm(dev, 0xa, 0x6);
		write_phy_ofdm(dev, 0xb, 0x99);
		write_phy_ofdm(dev, 0xf, 0x20);
		write_phy_ofdm(dev, 0x11, 0x7);

		rtl8225z2_set_gain(dev,4);

		write_phy_ofdm(dev,0x15, 0x40);
		write_phy_ofdm(dev,0x17, 0x40);

		write_nic_dword(dev, 0x94,0x10000000);
	} else {
		write_rtl8225(dev, 0x5, 0x1864);
		write_nic_dword(dev, RF_PARA, 0x10044);
		write_nic_dword(dev, RF_TIMING, 0xa8008);
		write_phy_ofdm(dev, 0x0, 0x1);
		write_phy_ofdm(dev, 0xa, 0x6);
		write_phy_ofdm(dev, 0xb, 0x99);
		write_phy_ofdm(dev, 0xf, 0x20);
		write_phy_ofdm(dev, 0x11, 0x7);

		rtl8225z2_set_gain(dev,4);

		write_phy_ofdm(dev,0x15, 0x40);
		write_phy_ofdm(dev,0x17, 0x40);

		write_nic_dword(dev, 0x94,0x04000002);
	}
}