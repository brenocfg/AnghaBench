#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_rx_data {size_t security_idx; TYPE_6__* key; TYPE_7__* sdata; int /*<<< orphan*/  tkip_iv16; int /*<<< orphan*/  tkip_iv32; struct sk_buff* skb; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  ieee80211_rx_result ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_14__ {TYPE_1__ vif; } ;
struct TYPE_12__ {scalar_t__ cipher; int keyidx; int /*<<< orphan*/ * key; } ;
struct TYPE_10__ {int /*<<< orphan*/  mic_failures; TYPE_2__* rx; } ;
struct TYPE_11__ {TYPE_3__ tkip; } ;
struct TYPE_13__ {TYPE_5__ conf; TYPE_4__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  iv16; int /*<<< orphan*/  iv32; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int MICHAEL_MIC_LEN ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 size_t NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY ; 
 int /*<<< orphan*/  RX_CONTINUE ; 
 int /*<<< orphan*/  RX_DROP_UNUSABLE ; 
 int RX_FLAG_DECRYPTED ; 
 int RX_FLAG_IV_STRIPPED ; 
 int RX_FLAG_MMIC_ERROR ; 
 int RX_FLAG_MMIC_STRIPPED ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac80211_ev_michael_mic_failure (TYPE_7__*,int,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  michael_mic (int /*<<< orphan*/ *,struct ieee80211_hdr*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

ieee80211_rx_result
ieee80211_rx_h_michael_mic_verify(struct ieee80211_rx_data *rx)
{
	u8 *data, *key = NULL;
	size_t data_len;
	unsigned int hdrlen;
	u8 mic[MICHAEL_MIC_LEN];
	struct sk_buff *skb = rx->skb;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;

	/*
	 * it makes no sense to check for MIC errors on anything other
	 * than data frames.
	 */
	if (!ieee80211_is_data_present(hdr->frame_control))
		return RX_CONTINUE;

	/*
	 * No way to verify the MIC if the hardware stripped it or
	 * the IV with the key index. In this case we have solely rely
	 * on the driver to set RX_FLAG_MMIC_ERROR in the event of a
	 * MIC failure report.
	 */
	if (status->flag & (RX_FLAG_MMIC_STRIPPED | RX_FLAG_IV_STRIPPED)) {
		if (status->flag & RX_FLAG_MMIC_ERROR)
			goto mic_fail_no_key;

		if (!(status->flag & RX_FLAG_IV_STRIPPED) && rx->key &&
		    rx->key->conf.cipher == WLAN_CIPHER_SUITE_TKIP)
			goto update_iv;

		return RX_CONTINUE;
	}

	/*
	 * Some hardware seems to generate Michael MIC failure reports; even
	 * though, the frame was not encrypted with TKIP and therefore has no
	 * MIC. Ignore the flag them to avoid triggering countermeasures.
	 */
	if (!rx->key || rx->key->conf.cipher != WLAN_CIPHER_SUITE_TKIP ||
	    !(status->flag & RX_FLAG_DECRYPTED))
		return RX_CONTINUE;

	if (rx->sdata->vif.type == NL80211_IFTYPE_AP && rx->key->conf.keyidx) {
		/*
		 * APs with pairwise keys should never receive Michael MIC
		 * errors for non-zero keyidx because these are reserved for
		 * group keys and only the AP is sending real multicast
		 * frames in the BSS. (
		 */
		return RX_DROP_UNUSABLE;
	}

	if (status->flag & RX_FLAG_MMIC_ERROR)
		goto mic_fail;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	if (skb->len < hdrlen + MICHAEL_MIC_LEN)
		return RX_DROP_UNUSABLE;

	if (skb_linearize(rx->skb))
		return RX_DROP_UNUSABLE;
	hdr = (void *)skb->data;

	data = skb->data + hdrlen;
	data_len = skb->len - hdrlen - MICHAEL_MIC_LEN;
	key = &rx->key->conf.key[NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY];
	michael_mic(key, hdr, data, data_len, mic);
	if (memcmp(mic, data + data_len, MICHAEL_MIC_LEN) != 0)
		goto mic_fail;

	/* remove Michael MIC from payload */
	skb_trim(skb, skb->len - MICHAEL_MIC_LEN);

update_iv:
	/* update IV in key information to be able to detect replays */
	rx->key->u.tkip.rx[rx->security_idx].iv32 = rx->tkip_iv32;
	rx->key->u.tkip.rx[rx->security_idx].iv16 = rx->tkip_iv16;

	return RX_CONTINUE;

mic_fail:
	rx->key->u.tkip.mic_failures++;

mic_fail_no_key:
	/*
	 * In some cases the key can be unset - e.g. a multicast packet, in
	 * a driver that supports HW encryption. Send up the key idx only if
	 * the key is set.
	 */
	mac80211_ev_michael_mic_failure(rx->sdata,
					rx->key ? rx->key->conf.keyidx : -1,
					(void *) skb->data, NULL, GFP_ATOMIC);
	return RX_DROP_UNUSABLE;
}