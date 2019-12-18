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
struct zd_mac {int /*<<< orphan*/  chip; int /*<<< orphan*/  hw; } ;
struct zd_ctrlset {scalar_t__ next_frame_length; void* current_length; void* tx_length; int /*<<< orphan*/  modulation; scalar_t__ service; void* packet_length; } ;
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct ieee80211_rate {int /*<<< orphan*/  hw_value_short; int /*<<< orphan*/  hw_value; } ;
struct ieee80211_hdr {int dummy; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 unsigned int FCS_LEN ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_RC_USE_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  ZD_ASSERT (int) ; 
 int /*<<< orphan*/  ZD_RATE (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cs_set_control (struct zd_mac*,struct zd_ctrlset*,struct ieee80211_hdr*,struct ieee80211_tx_info*) ; 
 struct ieee80211_rate* ieee80211_get_tx_rate (int /*<<< orphan*/ ,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  le16_to_cpu (void*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int zd_calc_tx_length_us (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zd_chip_is_zd1211b (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fill_ctrlset(struct zd_mac *mac,
			struct sk_buff *skb)
{
	int r;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	unsigned int frag_len = skb->len + FCS_LEN;
	unsigned int packet_length;
	struct ieee80211_rate *txrate;
	struct zd_ctrlset *cs = (struct zd_ctrlset *)
		skb_push(skb, sizeof(struct zd_ctrlset));
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	ZD_ASSERT(frag_len <= 0xffff);

	txrate = ieee80211_get_tx_rate(mac->hw, info);

	cs->modulation = txrate->hw_value;
	if (info->control.rates[0].flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		cs->modulation = txrate->hw_value_short;

	cs->tx_length = cpu_to_le16(frag_len);

	cs_set_control(mac, cs, hdr, info);

	packet_length = frag_len + sizeof(struct zd_ctrlset) + 10;
	ZD_ASSERT(packet_length <= 0xffff);
	/* ZD1211B: Computing the length difference this way, gives us
	 * flexibility to compute the packet length.
	 */
	cs->packet_length = cpu_to_le16(zd_chip_is_zd1211b(&mac->chip) ?
			packet_length - frag_len : packet_length);

	/*
	 * CURRENT LENGTH:
	 * - transmit frame length in microseconds
	 * - seems to be derived from frame length
	 * - see Cal_Us_Service() in zdinlinef.h
	 * - if macp->bTxBurstEnable is enabled, then multiply by 4
	 *  - bTxBurstEnable is never set in the vendor driver
	 *
	 * SERVICE:
	 * - "for PLCP configuration"
	 * - always 0 except in some situations at 802.11b 11M
	 * - see line 53 of zdinlinef.h
	 */
	cs->service = 0;
	r = zd_calc_tx_length_us(&cs->service, ZD_RATE(cs->modulation),
		                 le16_to_cpu(cs->tx_length));
	if (r < 0)
		return r;
	cs->current_length = cpu_to_le16(r);
	cs->next_frame_length = 0;

	return 0;
}