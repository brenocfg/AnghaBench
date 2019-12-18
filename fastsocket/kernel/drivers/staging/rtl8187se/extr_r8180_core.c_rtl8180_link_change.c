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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct r8180_priv {int /*<<< orphan*/  chan; scalar_t__ card_8185; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_network {int /*<<< orphan*/  beacon_interval; scalar_t__ bssid; } ;
struct TYPE_2__ {struct ieee80211_network current_network; } ;

/* Variables and functions */
 scalar_t__ BEACON_INTERVAL ; 
 int /*<<< orphan*/  BEACON_INTERVAL_MASK ; 
 scalar_t__ BSSID ; 
 int /*<<< orphan*/  EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  EPROM_CMD_NORMAL ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_nic_dword (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8180_set_chan (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_set_mode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_update_msr (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 

void rtl8180_link_change(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u16 beacon_interval;
	struct ieee80211_network *net = &priv->ieee80211->current_network;

	rtl8180_update_msr(dev);

	rtl8180_set_mode(dev,EPROM_CMD_CONFIG);

	write_nic_dword(dev,BSSID,((u32*)net->bssid)[0]);
	write_nic_word(dev,BSSID+4,((u16*)net->bssid)[2]);

	beacon_interval  = read_nic_dword(dev,BEACON_INTERVAL);
	beacon_interval &= ~ BEACON_INTERVAL_MASK;
	beacon_interval |= net->beacon_interval;
	write_nic_dword(dev, BEACON_INTERVAL, beacon_interval);

	rtl8180_set_mode(dev, EPROM_CMD_NORMAL);

	if(priv->card_8185)
		rtl8180_set_chan(dev, priv->chan);
}