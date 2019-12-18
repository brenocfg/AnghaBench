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
typedef  int u8 ;
typedef  int u32 ;
struct r8180_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; scalar_t__ iw_mode; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ IW_MODE_MASTER ; 
 int /*<<< orphan*/  MSR ; 
 int MSR_LINK_ADHOC ; 
 int MSR_LINK_MANAGED ; 
 int MSR_LINK_MASK ; 
 int MSR_LINK_MASTER ; 
 int MSR_LINK_NONE ; 
 int MSR_LINK_SHIFT ; 
 int RX_CHECK_BSSID_SHIFT ; 
 int /*<<< orphan*/  RX_CONF ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8180_update_msr(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u8 msr;
	u32 rxconf;

	msr  = read_nic_byte(dev, MSR);
	msr &= ~ MSR_LINK_MASK;

	rxconf=read_nic_dword(dev,RX_CONF);

	if(priv->ieee80211->state == IEEE80211_LINKED)
	{
		if(priv->ieee80211->iw_mode == IW_MODE_ADHOC)
			msr |= (MSR_LINK_ADHOC<<MSR_LINK_SHIFT);
		else if (priv->ieee80211->iw_mode == IW_MODE_MASTER)
			msr |= (MSR_LINK_MASTER<<MSR_LINK_SHIFT);
		else if (priv->ieee80211->iw_mode == IW_MODE_INFRA)
			msr |= (MSR_LINK_MANAGED<<MSR_LINK_SHIFT);
		else
			msr |= (MSR_LINK_NONE<<MSR_LINK_SHIFT);
		rxconf |= (1<<RX_CHECK_BSSID_SHIFT);

	}else {
		msr |= (MSR_LINK_NONE<<MSR_LINK_SHIFT);
		rxconf &= ~(1<<RX_CHECK_BSSID_SHIFT);
	}

	write_nic_byte(dev, MSR, msr);
	write_nic_dword(dev, RX_CONF, rxconf);
}