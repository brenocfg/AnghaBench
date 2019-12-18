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
typedef  int u8 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_hdr_4addr {int dummy; } ;
struct ieee80211_ccmp_data {int* tx_b0; int* tx_b; int* tx_e; int* tx_s0; int key_idx; int /*<<< orphan*/  tfm; int /*<<< orphan*/ * tx_pn; } ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 scalar_t__ CCMP_HDR_LEN ; 
 int CCMP_MIC_LEN ; 
 int CCMP_PN_LEN ; 
 int /*<<< orphan*/  ccmp_init_blocks (int /*<<< orphan*/ ,struct ieee80211_hdr_4addr*,int /*<<< orphan*/ *,int,int*,int*,int*) ; 
 int /*<<< orphan*/  ieee80211_ccmp_aes_encrypt (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int* skb_push (struct sk_buff*,scalar_t__) ; 
 int* skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  xor_block (int*,int*,int) ; 

__attribute__((used)) static int ieee80211_ccmp_encrypt(struct sk_buff *skb, int hdr_len, void *priv)
{
	struct ieee80211_ccmp_data *key = priv;
	int data_len, i;
	u8 *pos;
	struct ieee80211_hdr_4addr *hdr;
	int blocks, last, len;
	u8 *mic;
	u8 *b0 = key->tx_b0;
	u8 *b = key->tx_b;
	u8 *e = key->tx_e;
	u8 *s0 = key->tx_s0;

	if (skb_headroom(skb) < CCMP_HDR_LEN ||
	    skb_tailroom(skb) < CCMP_MIC_LEN ||
	    skb->len < hdr_len)
		return -1;

	data_len = skb->len - hdr_len;
	pos = skb_push(skb, CCMP_HDR_LEN);
	memmove(pos, pos + CCMP_HDR_LEN, hdr_len);
	pos += hdr_len;
//	mic = skb_put(skb, CCMP_MIC_LEN);

	i = CCMP_PN_LEN - 1;
	while (i >= 0) {
		key->tx_pn[i]++;
		if (key->tx_pn[i] != 0)
			break;
		i--;
	}

	*pos++ = key->tx_pn[5];
	*pos++ = key->tx_pn[4];
	*pos++ = 0;
	*pos++ = (key->key_idx << 6) | (1 << 5) /* Ext IV included */;
	*pos++ = key->tx_pn[3];
	*pos++ = key->tx_pn[2];
	*pos++ = key->tx_pn[1];
	*pos++ = key->tx_pn[0];

	hdr = (struct ieee80211_hdr_4addr *)skb->data;
	//mic is moved to here by john
	mic = skb_put(skb, CCMP_MIC_LEN);

	ccmp_init_blocks(key->tfm, hdr, key->tx_pn, data_len, b0, b, s0);

	blocks = (data_len + AES_BLOCK_LEN - 1) / AES_BLOCK_LEN;
	last = data_len % AES_BLOCK_LEN;

	for (i = 1; i <= blocks; i++) {
		len = (i == blocks && last) ? last : AES_BLOCK_LEN;
		/* Authentication */
		xor_block(b, pos, len);
		ieee80211_ccmp_aes_encrypt(key->tfm, b, b);
		/* Encryption, with counter */
		b0[14] = (i >> 8) & 0xff;
		b0[15] = i & 0xff;
		ieee80211_ccmp_aes_encrypt(key->tfm, b0, e);
		xor_block(pos, e, len);
		pos += len;
	}

	for (i = 0; i < CCMP_MIC_LEN; i++)
		mic[i] = b[i] ^ s0[i];

	return 0;
}