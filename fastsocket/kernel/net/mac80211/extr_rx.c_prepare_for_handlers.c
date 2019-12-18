#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_12__ {int type; int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  remote_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  use_4addr; } ;
struct TYPE_11__ {TYPE_4__ wds; TYPE_2__ ibss; TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_6__ vif; TYPE_5__ u; TYPE_3__* dev; } ;
struct ieee80211_rx_status {int flag; int rate_idx; int /*<<< orphan*/  rx_flags; } ;
struct ieee80211_rx_data {int /*<<< orphan*/  sta; struct sk_buff* skb; struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr2; } ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  IEEE80211_RX_RA_MATCH ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int IFF_PROMISC ; 
#define  NL80211_IFTYPE_ADHOC 134 
#define  NL80211_IFTYPE_AP 133 
#define  NL80211_IFTYPE_AP_VLAN 132 
#define  NL80211_IFTYPE_MESH_POINT 131 
#define  NL80211_IFTYPE_P2P_DEVICE 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int RX_FLAG_HT ; 
 int RX_FLAG_VHT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_bssid_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee80211_get_bssid (struct ieee80211_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_ibss_rx_no_sta (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_probe_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_public_action (struct ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_for_handlers(struct ieee80211_rx_data *rx,
				struct ieee80211_hdr *hdr)
{
	struct ieee80211_sub_if_data *sdata = rx->sdata;
	struct sk_buff *skb = rx->skb;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	u8 *bssid = ieee80211_get_bssid(hdr, skb->len, sdata->vif.type);
	int multicast = is_multicast_ether_addr(hdr->addr1);

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_STATION:
		if (!bssid && !sdata->u.mgd.use_4addr)
			return 0;
		if (!multicast &&
		    !ether_addr_equal(sdata->vif.addr, hdr->addr1)) {
			if (!(sdata->dev->flags & IFF_PROMISC) ||
			    sdata->u.mgd.use_4addr)
				return 0;
			status->rx_flags &= ~IEEE80211_RX_RA_MATCH;
		}
		break;
	case NL80211_IFTYPE_ADHOC:
		if (!bssid)
			return 0;
		if (ieee80211_is_beacon(hdr->frame_control)) {
			return 1;
		} else if (!ieee80211_bssid_match(bssid, sdata->u.ibss.bssid)) {
			return 0;
		} else if (!multicast &&
			   !ether_addr_equal(sdata->vif.addr, hdr->addr1)) {
			if (!(sdata->dev->flags & IFF_PROMISC))
				return 0;
			status->rx_flags &= ~IEEE80211_RX_RA_MATCH;
		} else if (!rx->sta) {
			int rate_idx;
			if (status->flag & (RX_FLAG_HT | RX_FLAG_VHT))
				rate_idx = 0; /* TODO: HT/VHT rates */
			else
				rate_idx = status->rate_idx;
			ieee80211_ibss_rx_no_sta(sdata, bssid, hdr->addr2,
						 BIT(rate_idx));
		}
		break;
	case NL80211_IFTYPE_MESH_POINT:
		if (!multicast &&
		    !ether_addr_equal(sdata->vif.addr, hdr->addr1)) {
			if (!(sdata->dev->flags & IFF_PROMISC))
				return 0;

			status->rx_flags &= ~IEEE80211_RX_RA_MATCH;
		}
		break;
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_AP:
		if (!bssid) {
			if (!ether_addr_equal(sdata->vif.addr, hdr->addr1))
				return 0;
		} else if (!ieee80211_bssid_match(bssid, sdata->vif.addr)) {
			/*
			 * Accept public action frames even when the
			 * BSSID doesn't match, this is used for P2P
			 * and location updates. Note that mac80211
			 * itself never looks at these frames.
			 */
			if (!multicast &&
			    !ether_addr_equal(sdata->vif.addr, hdr->addr1))
				return 0;
			if (ieee80211_is_public_action(hdr, skb->len))
				return 1;
			if (!ieee80211_is_beacon(hdr->frame_control))
				return 0;
			status->rx_flags &= ~IEEE80211_RX_RA_MATCH;
		}
		break;
	case NL80211_IFTYPE_WDS:
		if (bssid || !ieee80211_is_data(hdr->frame_control))
			return 0;
		if (!ether_addr_equal(sdata->u.wds.remote_addr, hdr->addr2))
			return 0;
		break;
	case NL80211_IFTYPE_P2P_DEVICE:
		if (!ieee80211_is_public_action(hdr, skb->len) &&
		    !ieee80211_is_probe_req(hdr->frame_control) &&
		    !ieee80211_is_probe_resp(hdr->frame_control) &&
		    !ieee80211_is_beacon(hdr->frame_control))
			return 0;
		if (!ether_addr_equal(sdata->vif.addr, hdr->addr1) &&
		    !multicast)
			status->rx_flags &= ~IEEE80211_RX_RA_MATCH;
		break;
	default:
		/* should never get here */
		WARN_ON_ONCE(1);
		break;
	}

	return 1;
}