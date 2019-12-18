#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_3__ control; } ;
struct ieee80211_tx_data {TYPE_5__* key; TYPE_2__* local; struct sk_buff* skb; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  ieee80211_tx_result ;
struct TYPE_9__ {scalar_t__ cipher; int flags; int /*<<< orphan*/ * key; } ;
struct TYPE_10__ {TYPE_4__ conf; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {scalar_t__ set_frag_threshold; } ;

/* Variables and functions */
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_DONTFRAG ; 
 int IEEE80211_TX_INTFL_TKIP_MIC_FAILURE ; 
 int MICHAEL_MIC_LEN ; 
 size_t NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY ; 
 scalar_t__ TKIP_ICV_LEN ; 
 scalar_t__ TKIP_IV_LEN ; 
 int /*<<< orphan*/  TX_CONTINUE ; 
 int /*<<< orphan*/  TX_DROP ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  michael_mic (int /*<<< orphan*/ *,struct ieee80211_hdr*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

ieee80211_tx_result
ieee80211_tx_h_michael_mic_add(struct ieee80211_tx_data *tx)
{
	u8 *data, *key, *mic;
	size_t data_len;
	unsigned int hdrlen;
	struct ieee80211_hdr *hdr;
	struct sk_buff *skb = tx->skb;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	int tail;

	hdr = (struct ieee80211_hdr *)skb->data;
	if (!tx->key || tx->key->conf.cipher != WLAN_CIPHER_SUITE_TKIP ||
	    skb->len < 24 || !ieee80211_is_data_present(hdr->frame_control))
		return TX_CONTINUE;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	if (skb->len < hdrlen)
		return TX_DROP;

	data = skb->data + hdrlen;
	data_len = skb->len - hdrlen;

	if (unlikely(info->flags & IEEE80211_TX_INTFL_TKIP_MIC_FAILURE)) {
		/* Need to use software crypto for the test */
		info->control.hw_key = NULL;
	}

	if (info->control.hw_key &&
	    (info->flags & IEEE80211_TX_CTL_DONTFRAG ||
	     tx->local->ops->set_frag_threshold) &&
	    !(tx->key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_MMIC)) {
		/* hwaccel - with no need for SW-generated MMIC */
		return TX_CONTINUE;
	}

	tail = MICHAEL_MIC_LEN;
	if (!info->control.hw_key)
		tail += TKIP_ICV_LEN;

	if (WARN_ON(skb_tailroom(skb) < tail ||
		    skb_headroom(skb) < TKIP_IV_LEN))
		return TX_DROP;

	key = &tx->key->conf.key[NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY];
	mic = skb_put(skb, MICHAEL_MIC_LEN);
	michael_mic(key, hdr, data, data_len, mic);
	if (unlikely(info->flags & IEEE80211_TX_INTFL_TKIP_MIC_FAILURE))
		mic[0]++;

	return TX_CONTINUE;
}