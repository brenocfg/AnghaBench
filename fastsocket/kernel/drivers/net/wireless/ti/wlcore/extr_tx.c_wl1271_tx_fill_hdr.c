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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {size_t global_hlid; int mgmt_rate_idx; size_t bcast_hlid; int bcast_rate_idx; int* ucast_rate_idx; } ;
struct TYPE_3__ {int basic_rate_idx; int p2p_rate_idx; int ap_rate_idx; } ;
struct wl12xx_vif {scalar_t__ bss_type; TYPE_2__ ap; TYPE_1__ sta; } ;
struct wl1271_tx_hw_descr {size_t hlid; void* tx_attr; int /*<<< orphan*/  tid; void* life_time; int /*<<< orphan*/  start_time; } ;
struct wl1271 {size_t* session_ids; int quirks; scalar_t__ time_offset; } ;
struct timespec {int dummy; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  priority; scalar_t__ data; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 int IEEE80211_TX_CTL_NO_CCK_RATE ; 
 size_t SESSION_COUNTER_INVALID ; 
 int TX_HW_AP_MODE_PKT_LIFETIME_TU ; 
 int TX_HW_ATTR_HOST_ENCRYPT ; 
 int TX_HW_ATTR_OFST_RATE_POLICY ; 
 size_t TX_HW_ATTR_OFST_SESSION_COUNTER ; 
 size_t TX_HW_ATTR_SESSION_COUNTER ; 
 int TX_HW_ATTR_TX_DUMMY_REQ ; 
 int TX_HW_MGMT_PKT_LIFETIME_TU ; 
 int WLCORE_QUIRK_AP_ZERO_SESSION_ID ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  getnstimeofday (struct timespec*) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (size_t*,struct ieee80211_hdr*,int) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int) ; 
 int timespec_to_ns (struct timespec*) ; 
 int wl1271_tx_get_queue (int /*<<< orphan*/ ) ; 
 int wl12xx_is_dummy_packet (struct wl1271*,struct sk_buff*) ; 
 int /*<<< orphan*/  wlcore_hw_set_tx_desc_csum (struct wl1271*,struct wl1271_tx_hw_descr*,struct sk_buff*) ; 
 int /*<<< orphan*/  wlcore_hw_set_tx_desc_data_len (struct wl1271*,struct wl1271_tx_hw_descr*,struct sk_buff*) ; 

__attribute__((used)) static void wl1271_tx_fill_hdr(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			       struct sk_buff *skb, u32 extra,
			       struct ieee80211_tx_info *control, u8 hlid)
{
	struct timespec ts;
	struct wl1271_tx_hw_descr *desc;
	int ac, rate_idx;
	s64 hosttime;
	u16 tx_attr = 0;
	__le16 frame_control;
	struct ieee80211_hdr *hdr;
	u8 *frame_start;
	bool is_dummy;

	desc = (struct wl1271_tx_hw_descr *) skb->data;
	frame_start = (u8 *)(desc + 1);
	hdr = (struct ieee80211_hdr *)(frame_start + extra);
	frame_control = hdr->frame_control;

	/* relocate space for security header */
	if (extra) {
		int hdrlen = ieee80211_hdrlen(frame_control);
		memmove(frame_start, hdr, hdrlen);
		skb_set_network_header(skb, skb_network_offset(skb) + extra);
	}

	/* configure packet life time */
	getnstimeofday(&ts);
	hosttime = (timespec_to_ns(&ts) >> 10);
	desc->start_time = cpu_to_le32(hosttime - wl->time_offset);

	is_dummy = wl12xx_is_dummy_packet(wl, skb);
	if (is_dummy || !wlvif || wlvif->bss_type != BSS_TYPE_AP_BSS)
		desc->life_time = cpu_to_le16(TX_HW_MGMT_PKT_LIFETIME_TU);
	else
		desc->life_time = cpu_to_le16(TX_HW_AP_MODE_PKT_LIFETIME_TU);

	/* queue */
	ac = wl1271_tx_get_queue(skb_get_queue_mapping(skb));
	desc->tid = skb->priority;

	if (is_dummy) {
		/*
		 * FW expects the dummy packet to have an invalid session id -
		 * any session id that is different than the one set in the join
		 */
		tx_attr = (SESSION_COUNTER_INVALID <<
			   TX_HW_ATTR_OFST_SESSION_COUNTER) &
			   TX_HW_ATTR_SESSION_COUNTER;

		tx_attr |= TX_HW_ATTR_TX_DUMMY_REQ;
	} else if (wlvif) {
		u8 session_id = wl->session_ids[hlid];

		if ((wl->quirks & WLCORE_QUIRK_AP_ZERO_SESSION_ID) &&
		    (wlvif->bss_type == BSS_TYPE_AP_BSS))
			session_id = 0;

		/* configure the tx attributes */
		tx_attr = session_id << TX_HW_ATTR_OFST_SESSION_COUNTER;
	}

	desc->hlid = hlid;
	if (is_dummy || !wlvif)
		rate_idx = 0;
	else if (wlvif->bss_type != BSS_TYPE_AP_BSS) {
		/*
		 * if the packets are data packets
		 * send them with AP rate policies (EAPOLs are an exception),
		 * otherwise use default basic rates
		 */
		if (skb->protocol == cpu_to_be16(ETH_P_PAE))
			rate_idx = wlvif->sta.basic_rate_idx;
		else if (control->flags & IEEE80211_TX_CTL_NO_CCK_RATE)
			rate_idx = wlvif->sta.p2p_rate_idx;
		else if (ieee80211_is_data(frame_control))
			rate_idx = wlvif->sta.ap_rate_idx;
		else
			rate_idx = wlvif->sta.basic_rate_idx;
	} else {
		if (hlid == wlvif->ap.global_hlid)
			rate_idx = wlvif->ap.mgmt_rate_idx;
		else if (hlid == wlvif->ap.bcast_hlid ||
			 skb->protocol == cpu_to_be16(ETH_P_PAE) ||
			 !ieee80211_is_data(frame_control))
			/*
			 * send non-data, bcast and EAPOLs using the
			 * min basic rate
			 */
			rate_idx = wlvif->ap.bcast_rate_idx;
		else
			rate_idx = wlvif->ap.ucast_rate_idx[ac];
	}

	tx_attr |= rate_idx << TX_HW_ATTR_OFST_RATE_POLICY;

	/* for WEP shared auth - no fw encryption is needed */
	if (ieee80211_is_auth(frame_control) &&
	    ieee80211_has_protected(frame_control))
		tx_attr |= TX_HW_ATTR_HOST_ENCRYPT;

	desc->tx_attr = cpu_to_le16(tx_attr);

	wlcore_hw_set_tx_desc_csum(wl, desc, skb);
	wlcore_hw_set_tx_desc_data_len(wl, desc, skb);
}