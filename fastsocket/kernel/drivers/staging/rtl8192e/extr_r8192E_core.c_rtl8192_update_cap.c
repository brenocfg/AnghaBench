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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct r8192_priv {int short_preamble; int /*<<< orphan*/  slot_time; TYPE_2__* ieee80211; int /*<<< orphan*/  basic_rate; } ;
struct net_device {int dummy; } ;
struct ieee80211_network {int mode; } ;
struct TYPE_4__ {TYPE_1__* pHTInfo; struct ieee80211_network current_network; } ;
struct TYPE_3__ {int /*<<< orphan*/  bCurrentRT2RTLongSlotTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRSR_AckShortPmb ; 
 int IEEE_G ; 
 int IEEE_N_24G ; 
 int /*<<< orphan*/  NON_SHORT_SLOT_TIME ; 
 int /*<<< orphan*/  RRSR ; 
 int /*<<< orphan*/  SHORT_SLOT_TIME ; 
 int /*<<< orphan*/  SLOT_TIME ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int WLAN_CAPABILITY_SHORT_SLOT ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8192_update_cap(struct net_device* dev, u16 cap)
{
	u32 tmp = 0;
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct ieee80211_network *net = &priv->ieee80211->current_network;
	priv->short_preamble = cap & WLAN_CAPABILITY_SHORT_PREAMBLE;
	tmp = priv->basic_rate;
	if (priv->short_preamble)
		tmp |= BRSR_AckShortPmb;
	write_nic_dword(dev, RRSR, tmp);

	if (net->mode & (IEEE_G|IEEE_N_24G))
	{
		u8 slot_time = 0;
		if ((cap & WLAN_CAPABILITY_SHORT_SLOT)&&(!priv->ieee80211->pHTInfo->bCurrentRT2RTLongSlotTime))
		{//short slot time
			slot_time = SHORT_SLOT_TIME;
		}
		else //long slot time
			slot_time = NON_SHORT_SLOT_TIME;
		priv->slot_time = slot_time;
		write_nic_byte(dev, SLOT_TIME, slot_time);
	}

}