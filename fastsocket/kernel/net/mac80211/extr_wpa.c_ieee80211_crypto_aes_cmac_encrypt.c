#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ hw_key; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_tx_data {int /*<<< orphan*/  skbs; struct ieee80211_key* key; } ;
struct ieee80211_mmie {int length; int /*<<< orphan*/  mic; int /*<<< orphan*/  sequence_number; int /*<<< orphan*/  key_id; int /*<<< orphan*/  element_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  tfm; int /*<<< orphan*/  tx_pn; } ;
struct TYPE_8__ {TYPE_3__ aes_cmac; } ;
struct TYPE_6__ {int /*<<< orphan*/  keyidx; } ;
struct ieee80211_key {TYPE_4__ u; TYPE_2__ conf; } ;
typedef  int /*<<< orphan*/  ieee80211_tx_result ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  TX_CONTINUE ; 
 int /*<<< orphan*/  TX_DROP ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_EID_MMIE ; 
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bip_aad (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bip_ipn_set64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_aes_cmac (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int skb_tailroom (struct sk_buff*) ; 

ieee80211_tx_result
ieee80211_crypto_aes_cmac_encrypt(struct ieee80211_tx_data *tx)
{
	struct sk_buff *skb;
	struct ieee80211_tx_info *info;
	struct ieee80211_key *key = tx->key;
	struct ieee80211_mmie *mmie;
	u8 aad[20];
	u64 pn64;

	if (WARN_ON(skb_queue_len(&tx->skbs) != 1))
		return TX_DROP;

	skb = skb_peek(&tx->skbs);

	info = IEEE80211_SKB_CB(skb);

	if (info->control.hw_key)
		return TX_CONTINUE;

	if (WARN_ON(skb_tailroom(skb) < sizeof(*mmie)))
		return TX_DROP;

	mmie = (struct ieee80211_mmie *) skb_put(skb, sizeof(*mmie));
	mmie->element_id = WLAN_EID_MMIE;
	mmie->length = sizeof(*mmie) - 2;
	mmie->key_id = cpu_to_le16(key->conf.keyidx);

	/* PN = PN + 1 */
	pn64 = atomic64_inc_return(&key->u.aes_cmac.tx_pn);

	bip_ipn_set64(mmie->sequence_number, pn64);

	bip_aad(skb, aad);

	/*
	 * MIC = AES-128-CMAC(IGTK, AAD || Management Frame Body || MMIE, 64)
	 */
	ieee80211_aes_cmac(key->u.aes_cmac.tfm, aad,
			   skb->data + 24, skb->len - 24, mmie->mic);

	return TX_CONTINUE;
}