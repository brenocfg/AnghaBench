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
struct ieee80211_device {int softmac_features; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* link_change ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  state; int /*<<< orphan*/  (* data_hard_stop ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Dot11d_Reset (struct ieee80211_device*) ; 
 int /*<<< orphan*/  IEEE80211_NOLINK ; 
 int IEEE_SOFTMAC_TX_QUEUE ; 
 scalar_t__ IS_DOT11D_ENABLE (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_reset_queue (struct ieee80211_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_wx_assoc_event (struct ieee80211_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void ieee80211_disassociate(struct ieee80211_device *ieee)
{
	netif_carrier_off(ieee->dev);

	if (ieee->softmac_features & IEEE_SOFTMAC_TX_QUEUE)
			ieee80211_reset_queue(ieee);

	if (ieee->data_hard_stop)
			ieee->data_hard_stop(ieee->dev);

	if(IS_DOT11D_ENABLE(ieee))
		Dot11d_Reset(ieee);
	ieee->state = IEEE80211_NOLINK;
	ieee->link_change(ieee->dev);
	notify_wx_assoc_event(ieee);

}