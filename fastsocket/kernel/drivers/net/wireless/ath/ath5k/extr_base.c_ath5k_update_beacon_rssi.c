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
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  bssid; int /*<<< orphan*/  frame_control; } ;
struct ath_common {int /*<<< orphan*/  curbssid; } ;
struct ath5k_hw {int /*<<< orphan*/  ah_beacon_rssi_avg; } ;

/* Variables and functions */
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewma_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_update_beacon_rssi(struct ath5k_hw *ah, struct sk_buff *skb, int rssi)
{
	struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)skb->data;
	struct ath_common *common = ath5k_hw_common(ah);

	/* only beacons from our BSSID */
	if (!ieee80211_is_beacon(mgmt->frame_control) ||
	    !ether_addr_equal(mgmt->bssid, common->curbssid))
		return;

	ewma_add(&ah->ah_beacon_rssi_avg, rssi);

	/* in IBSS mode we should keep RSSI statistics per neighbour */
	/* le16_to_cpu(mgmt->u.beacon.capab_info) & WLAN_CAPABILITY_IBSS */
}