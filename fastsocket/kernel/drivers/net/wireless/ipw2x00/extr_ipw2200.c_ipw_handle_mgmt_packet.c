#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  cb; int /*<<< orphan*/  protocol; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct libipw_rx_stats {int dummy; } ;
struct libipw_hdr_4addr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_ctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {TYPE_1__ frame; } ;
struct ipw_rx_packet {TYPE_2__ u; } ;
struct ipw_rx_mem_buffer {struct sk_buff* skb; } ;
struct ipw_priv {int config; TYPE_3__* ieee; int /*<<< orphan*/  bssid; } ;
struct TYPE_6__ {scalar_t__ iw_mode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CFG_NET_STATS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_80211_STATS ; 
 scalar_t__ IEEE80211_STYPE_BEACON ; 
 scalar_t__ IEEE80211_STYPE_PROBE_RESP ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*) ; 
 scalar_t__ IPW_RX_FRAME_SIZE ; 
 scalar_t__ IW_MODE_ADHOC ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 scalar_t__ WLAN_FC_GET_STYPE (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_add_station (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libipw_rx_mgt (TYPE_3__*,struct libipw_hdr_4addr*,struct libipw_rx_stats*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct libipw_rx_stats*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void ipw_handle_mgmt_packet(struct ipw_priv *priv,
				   struct ipw_rx_mem_buffer *rxb,
				   struct libipw_rx_stats *stats)
{
	struct sk_buff *skb = rxb->skb;
	struct ipw_rx_packet *pkt = (struct ipw_rx_packet *)skb->data;
	struct libipw_hdr_4addr *header = (struct libipw_hdr_4addr *)
	    (skb->data + IPW_RX_FRAME_SIZE);

	libipw_rx_mgt(priv->ieee, header, stats);

	if (priv->ieee->iw_mode == IW_MODE_ADHOC &&
	    ((WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)) ==
	      IEEE80211_STYPE_PROBE_RESP) ||
	     (WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)) ==
	      IEEE80211_STYPE_BEACON))) {
		if (!memcmp(header->addr3, priv->bssid, ETH_ALEN))
			ipw_add_station(priv, header->addr2);
	}

	if (priv->config & CFG_NET_STATS) {
		IPW_DEBUG_HC("sending stat packet\n");

		/* Set the size of the skb to the size of the full
		 * ipw header and 802.11 frame */
		skb_put(skb, le16_to_cpu(pkt->u.frame.length) +
			IPW_RX_FRAME_SIZE);

		/* Advance past the ipw packet header to the 802.11 frame */
		skb_pull(skb, IPW_RX_FRAME_SIZE);

		/* Push the libipw_rx_stats before the 802.11 frame */
		memcpy(skb_push(skb, sizeof(*stats)), stats, sizeof(*stats));

		skb->dev = priv->ieee->dev;

		/* Point raw at the libipw_stats */
		skb_reset_mac_header(skb);

		skb->pkt_type = PACKET_OTHERHOST;
		skb->protocol = cpu_to_be16(ETH_P_80211_STATS);
		memset(skb->cb, 0, sizeof(rxb->skb->cb));
		netif_rx(skb);
		rxb->skb = NULL;
	}
}