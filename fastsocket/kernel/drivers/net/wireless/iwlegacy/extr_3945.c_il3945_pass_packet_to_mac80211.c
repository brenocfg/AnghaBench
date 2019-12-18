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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct il_rx_pkt {int dummy; } ;
struct il_rx_buf {int /*<<< orphan*/ * page; } ;
struct TYPE_3__ {int rx_page_order; } ;
struct il_priv {int /*<<< orphan*/  alloc_rxb_page; int /*<<< orphan*/  hw; int /*<<< orphan*/  is_open; TYPE_1__ hw_params; } ;
struct il3945_rx_frame_hdr {scalar_t__ payload; int /*<<< orphan*/  len; } ;
struct il3945_rx_frame_end {int /*<<< orphan*/  status; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  sw_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_DROP (char*) ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 scalar_t__ IL39_RX_FRAME_SIZE ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 scalar_t__ IL_RX_DATA (struct il_rx_pkt*) ; 
 struct il3945_rx_frame_end* IL_RX_END (struct il_rx_pkt*) ; 
 struct il3945_rx_frame_hdr* IL_RX_HDR (struct il_rx_pkt*) ; 
 scalar_t__ PAGE_SIZE ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  ieee80211_rx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 TYPE_2__ il3945_mod_params ; 
 int /*<<< orphan*/  il_set_decrypted_flag (struct il_priv*,struct ieee80211_hdr*,int /*<<< orphan*/ ,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  il_update_stats (struct il_priv*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
il3945_pass_packet_to_mac80211(struct il_priv *il, struct il_rx_buf *rxb,
			       struct ieee80211_rx_status *stats)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)IL_RX_DATA(pkt);
	struct il3945_rx_frame_hdr *rx_hdr = IL_RX_HDR(pkt);
	struct il3945_rx_frame_end *rx_end = IL_RX_END(pkt);
	u16 len = le16_to_cpu(rx_hdr->len);
	struct sk_buff *skb;
	__le16 fc = hdr->frame_control;

	/* We received data from the HW, so stop the watchdog */
	if (unlikely
	    (len + IL39_RX_FRAME_SIZE >
	     PAGE_SIZE << il->hw_params.rx_page_order)) {
		D_DROP("Corruption detected!\n");
		return;
	}

	/* We only process data packets if the interface is open */
	if (unlikely(!il->is_open)) {
		D_DROP("Dropping packet while interface is not open.\n");
		return;
	}

	skb = dev_alloc_skb(128);
	if (!skb) {
		IL_ERR("dev_alloc_skb failed\n");
		return;
	}

	if (!il3945_mod_params.sw_crypto)
		il_set_decrypted_flag(il, (struct ieee80211_hdr *)rxb_addr(rxb),
				      le32_to_cpu(rx_end->status), stats);

	skb_add_rx_frag(skb, 0, rxb->page,
			(void *)rx_hdr->payload - (void *)pkt, len,
			len);

	il_update_stats(il, false, fc, len);
	memcpy(IEEE80211_SKB_RXCB(skb), stats, sizeof(*stats));

	ieee80211_rx(il->hw, skb);
	il->alloc_rxb_page--;
	rxb->page = NULL;
}