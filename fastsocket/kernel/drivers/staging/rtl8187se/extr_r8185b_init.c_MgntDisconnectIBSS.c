#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct r8180_priv {TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int* bssid; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* link_change ) (struct net_device*) ;int /*<<< orphan*/  state; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  DrvIFIndicateDisassociation (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_NOLINK ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_stop_send_beacons (TYPE_2__*) ; 
 int /*<<< orphan*/  notify_wx_assoc_event (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  unspec_reason ; 

void
MgntDisconnectIBSS(
	struct net_device *dev
)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	u8			i;

	//printk("XXXXXXXXXX MgntDisconnect IBSS\n");

	DrvIFIndicateDisassociation(dev, unspec_reason);

//	PlatformZeroMemory( pMgntInfo->Bssid, 6 );
	for(i=0;i<6;i++)  priv->ieee80211->current_network.bssid[i] = 0x55;

	priv->ieee80211->state = IEEE80211_NOLINK;

	//Stop Beacon.

	// Vista add a Adhoc profile, HW radio off untill OID_DOT11_RESET_REQUEST
	// Driver would set MSR=NO_LINK, then HW Radio ON, MgntQueue Stuck.
	// Because Bcn DMA isn't complete, mgnt queue would stuck until Bcn packet send.

	// Disable Beacon Queue Own bit, suggested by jong
//	Adapter->HalFunc.SetTxDescOWNHandler(Adapter, BEACON_QUEUE, 0, 0);
	ieee80211_stop_send_beacons(priv->ieee80211);

	priv->ieee80211->link_change(dev);
	notify_wx_assoc_event(priv->ieee80211);

	// Stop SW Beacon.Use hw beacon so do not need to do so.by amy

//		MgntIndicateMediaStatus( Adapter, RT_MEDIA_DISCONNECT, GENERAL_INDICATE );

}