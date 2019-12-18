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
struct r8180_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ IEEE_B ; 
 scalar_t__ IEEE_G ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__* rtl8225z2_gain_a ; 
 scalar_t__* rtl8225z2_gain_bg ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,scalar_t__ const) ; 

void rtl8225z2_set_gain(struct net_device *dev, short gain)
{
	const u8 *rtl8225_gain;
	struct r8180_priv *priv = ieee80211_priv(dev);
	u8 mode = priv->ieee80211->mode;

	if (mode == IEEE_B || mode == IEEE_G)
		rtl8225_gain = rtl8225z2_gain_bg;
	else
		rtl8225_gain = rtl8225z2_gain_a;

	write_phy_ofdm(dev, 0x0b, rtl8225_gain[gain * 3]);
	write_phy_ofdm(dev, 0x1b, rtl8225_gain[gain * 3 + 1]);
	write_phy_ofdm(dev, 0x1d, rtl8225_gain[gain * 3 + 2]);
	write_phy_ofdm(dev, 0x21, 0x37);
}