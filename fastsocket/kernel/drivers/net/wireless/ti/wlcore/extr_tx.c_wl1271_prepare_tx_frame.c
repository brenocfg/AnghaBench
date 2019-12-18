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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct wl12xx_vif {scalar_t__ default_key; scalar_t__ bss_type; } ;
struct wl1271_tx_hw_descr {int dummy; } ;
struct wl1271 {int quirks; scalar_t__ aggr_buf; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__* hw_key; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct TYPE_3__ {scalar_t__ cipher; scalar_t__ hw_key_idx; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int EINVAL ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 scalar_t__ WL1271_CIPHER_SUITE_GEM ; 
 scalar_t__ WL1271_EXTRA_SPACE_TKIP ; 
 scalar_t__ WL12XX_INVALID_LINK_ID ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 int WLCORE_QUIRK_TKIP_HEADER_SPACE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 
 int wl1271_set_default_wep_key (struct wl1271*,struct wl12xx_vif*,scalar_t__) ; 
 int wl1271_tx_allocate (struct wl1271*,struct wl12xx_vif*,struct sk_buff*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  wl1271_tx_ap_update_inconnection_sta (struct wl1271*,struct sk_buff*) ; 
 int /*<<< orphan*/  wl1271_tx_fill_hdr (struct wl1271*,struct wl12xx_vif*,struct sk_buff*,scalar_t__,struct ieee80211_tx_info*,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_tx_regulate_link (struct wl1271*,struct wl12xx_vif*,scalar_t__) ; 
 int wl12xx_is_dummy_packet (struct wl1271*,struct sk_buff*) ; 
 scalar_t__ wlcore_calc_packet_alignment (struct wl1271*,scalar_t__) ; 

__attribute__((used)) static int wl1271_prepare_tx_frame(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				   struct sk_buff *skb, u32 buf_offset, u8 hlid)
{
	struct ieee80211_tx_info *info;
	u32 extra = 0;
	int ret = 0;
	u32 total_len;
	bool is_dummy;
	bool is_gem = false;

	if (!skb) {
		wl1271_error("discarding null skb");
		return -EINVAL;
	}

	if (hlid == WL12XX_INVALID_LINK_ID) {
		wl1271_error("invalid hlid. dropping skb 0x%p", skb);
		return -EINVAL;
	}

	info = IEEE80211_SKB_CB(skb);

	is_dummy = wl12xx_is_dummy_packet(wl, skb);

	if ((wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE) &&
	    info->control.hw_key &&
	    info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP)
		extra = WL1271_EXTRA_SPACE_TKIP;

	if (info->control.hw_key) {
		bool is_wep;
		u8 idx = info->control.hw_key->hw_key_idx;
		u32 cipher = info->control.hw_key->cipher;

		is_wep = (cipher == WLAN_CIPHER_SUITE_WEP40) ||
			 (cipher == WLAN_CIPHER_SUITE_WEP104);

		if (unlikely(is_wep && wlvif->default_key != idx)) {
			ret = wl1271_set_default_wep_key(wl, wlvif, idx);
			if (ret < 0)
				return ret;
			wlvif->default_key = idx;
		}

		is_gem = (cipher == WL1271_CIPHER_SUITE_GEM);
	}

	ret = wl1271_tx_allocate(wl, wlvif, skb, extra, buf_offset, hlid,
				 is_gem);
	if (ret < 0)
		return ret;

	wl1271_tx_fill_hdr(wl, wlvif, skb, extra, info, hlid);

	if (!is_dummy && wlvif && wlvif->bss_type == BSS_TYPE_AP_BSS) {
		wl1271_tx_ap_update_inconnection_sta(wl, skb);
		wl1271_tx_regulate_link(wl, wlvif, hlid);
	}

	/*
	 * The length of each packet is stored in terms of
	 * words. Thus, we must pad the skb data to make sure its
	 * length is aligned.  The number of padding bytes is computed
	 * and set in wl1271_tx_fill_hdr.
	 * In special cases, we want to align to a specific block size
	 * (eg. for wl128x with SDIO we align to 256).
	 */
	total_len = wlcore_calc_packet_alignment(wl, skb->len);

	memcpy(wl->aggr_buf + buf_offset, skb->data, skb->len);
	memset(wl->aggr_buf + buf_offset + skb->len, 0, total_len - skb->len);

	/* Revert side effects in the dummy packet skb, so it can be reused */
	if (is_dummy)
		skb_pull(skb, sizeof(struct wl1271_tx_hw_descr));

	return total_len;
}