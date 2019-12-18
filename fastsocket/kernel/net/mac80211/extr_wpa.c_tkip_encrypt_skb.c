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
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct TYPE_11__ {TYPE_4__* hw_key; } ;
struct ieee80211_tx_info {TYPE_5__ control; } ;
struct ieee80211_tx_data {TYPE_6__* local; struct ieee80211_key* key; } ;
struct TYPE_7__ {scalar_t__ iv16; int /*<<< orphan*/  iv32; } ;
struct TYPE_8__ {int /*<<< orphan*/  txlock; TYPE_1__ tx; } ;
struct TYPE_9__ {TYPE_2__ tkip; } ;
struct ieee80211_key {TYPE_3__ u; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_12__ {int /*<<< orphan*/  wep_tx_tfm; } ;
struct TYPE_10__ {int flags; } ;

/* Variables and functions */
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_PUT_IV_SPACE ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int TKIP_ICV_LEN ; 
 scalar_t__ TKIP_IV_LEN ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee80211_tkip_add_iv (int /*<<< orphan*/ *,struct ieee80211_key*) ; 
 int ieee80211_tkip_encrypt_data (int /*<<< orphan*/ ,struct ieee80211_key*,struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tkip_encrypt_skb(struct ieee80211_tx_data *tx, struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	struct ieee80211_key *key = tx->key;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	unsigned int hdrlen;
	int len, tail;
	u8 *pos;

	if (info->control.hw_key &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_GENERATE_IV) &&
	    !(info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE)) {
		/* hwaccel - with no need for software-generated IV */
		return 0;
	}

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	len = skb->len - hdrlen;

	if (info->control.hw_key)
		tail = 0;
	else
		tail = TKIP_ICV_LEN;

	if (WARN_ON(skb_tailroom(skb) < tail ||
		    skb_headroom(skb) < TKIP_IV_LEN))
		return -1;

	pos = skb_push(skb, TKIP_IV_LEN);
	memmove(pos, pos + TKIP_IV_LEN, hdrlen);
	skb_set_network_header(skb, skb_network_offset(skb) + TKIP_IV_LEN);
	pos += hdrlen;

	/* the HW only needs room for the IV, but not the actual IV */
	if (info->control.hw_key &&
	    (info->control.hw_key->flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE))
		return 0;

	/* Increase IV for the frame */
	spin_lock(&key->u.tkip.txlock);
	key->u.tkip.tx.iv16++;
	if (key->u.tkip.tx.iv16 == 0)
		key->u.tkip.tx.iv32++;
	pos = ieee80211_tkip_add_iv(pos, key);
	spin_unlock(&key->u.tkip.txlock);

	/* hwaccel - with software IV */
	if (info->control.hw_key)
		return 0;

	/* Add room for ICV */
	skb_put(skb, TKIP_ICV_LEN);

	return ieee80211_tkip_encrypt_data(tx->local->wep_tx_tfm,
					   key, skb, pos, len);
}