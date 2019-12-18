#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_rx_data {TYPE_2__* skb; scalar_t__ key; TYPE_1__* sdata; scalar_t__ sta; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_7__ {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (TYPE_2__*) ; 
 int RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  WLAN_STA_MFP ; 
 int /*<<< orphan*/  cfg80211_send_unprot_deauth (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_send_unprot_disassoc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_get_mmie_keyidx (TYPE_2__*) ; 
 int /*<<< orphan*/  ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_action (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_disassoc (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_multicast_robust_mgmt_frame (TYPE_2__*) ; 
 scalar_t__ ieee80211_is_robust_mgmt_frame (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_unicast_robust_mgmt_frame (TYPE_2__*) ; 
 scalar_t__ test_sta_flag (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ieee80211_drop_unencrypted_mgmt(struct ieee80211_rx_data *rx)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)rx->skb->data;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(rx->skb);
	__le16 fc = hdr->frame_control;

	/*
	 * Pass through unencrypted frames if the hardware has
	 * decrypted them already.
	 */
	if (status->flag & RX_FLAG_DECRYPTED)
		return 0;

	if (rx->sta && test_sta_flag(rx->sta, WLAN_STA_MFP)) {
		if (unlikely(!ieee80211_has_protected(fc) &&
			     ieee80211_is_unicast_robust_mgmt_frame(rx->skb) &&
			     rx->key)) {
			if (ieee80211_is_deauth(fc))
				cfg80211_send_unprot_deauth(rx->sdata->dev,
							    rx->skb->data,
							    rx->skb->len);
			else if (ieee80211_is_disassoc(fc))
				cfg80211_send_unprot_disassoc(rx->sdata->dev,
							      rx->skb->data,
							      rx->skb->len);
			return -EACCES;
		}
		/* BIP does not use Protected field, so need to check MMIE */
		if (unlikely(ieee80211_is_multicast_robust_mgmt_frame(rx->skb) &&
			     ieee80211_get_mmie_keyidx(rx->skb) < 0)) {
			if (ieee80211_is_deauth(fc))
				cfg80211_send_unprot_deauth(rx->sdata->dev,
							    rx->skb->data,
							    rx->skb->len);
			else if (ieee80211_is_disassoc(fc))
				cfg80211_send_unprot_disassoc(rx->sdata->dev,
							      rx->skb->data,
							      rx->skb->len);
			return -EACCES;
		}
		/*
		 * When using MFP, Action frames are not allowed prior to
		 * having configured keys.
		 */
		if (unlikely(ieee80211_is_action(fc) && !rx->key &&
			     ieee80211_is_robust_mgmt_frame(
				     (struct ieee80211_hdr *) rx->skb->data)))
			return -EACCES;
	}

	return 0;
}