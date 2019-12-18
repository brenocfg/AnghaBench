#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct r8192_priv {TYPE_3__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ mode; } ;
struct TYPE_6__ {TYPE_1__* pHTInfo; TYPE_2__ current_network; } ;
struct TYPE_4__ {int /*<<< orphan*/  bCurSuppCCK; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESG (char*) ; 
 scalar_t__ IEEE_A ; 
 scalar_t__ IEEE_N_24G ; 
 scalar_t__ IEEE_N_5G ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtl819xusb_beacon_tx (struct net_device*,int) ; 

void
cmdpkt_beacontimerinterrupt_819xusb(
	struct net_device *dev
)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u16 tx_rate;
	{
		//
		// 070117, rcnjko: 87B have to S/W beacon for DTM encryption_cmn.
		//
		if(priv->ieee80211->current_network.mode == IEEE_A  ||
			priv->ieee80211->current_network.mode == IEEE_N_5G ||
			(priv->ieee80211->current_network.mode == IEEE_N_24G  && (!priv->ieee80211->pHTInfo->bCurSuppCCK)))
		{
			tx_rate = 60;
			DMESG("send beacon frame  tx rate is 6Mbpm\n");
		}
		else
		{
			tx_rate =10;
			DMESG("send beacon frame  tx rate is 1Mbpm\n");
		}

		rtl819xusb_beacon_tx(dev,tx_rate); // HW Beacon

	}

}