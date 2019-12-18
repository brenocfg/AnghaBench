#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct rfmon_header {int flags; int rate; int rssi; int /*<<< orphan*/  freq; int /*<<< orphan*/  clock; } ;
struct avs_80211_1_header {void* encoding; void* preamble; void* ssi_noise; void* ssi_signal; void* ssi_type; void* priority; void* antenna; void* datarate; void* channel; void* phytype; void* hosttime; void* mactime; void* length; void* version; } ;
struct TYPE_7__ {int noise; } ;
struct TYPE_8__ {TYPE_2__ qual; } ;
struct TYPE_9__ {TYPE_3__ local_iwstatistics; TYPE_1__* ndev; } ;
typedef  TYPE_4__ islpci_private ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE80211_PRISM ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int P80211CAPTURE_VERSION ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int channel_of_freq (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static inline int
islpci_monitor_rx(islpci_private *priv, struct sk_buff **skb)
{
	/* The card reports full 802.11 packets but with a 20 bytes
	 * header and without the FCS. But there a is a bit that
	 * indicates if the packet is corrupted :-) */
	struct rfmon_header *hdr = (struct rfmon_header *) (*skb)->data;

	if (hdr->flags & 0x01)
		/* This one is bad. Drop it ! */
		return -1;
	if (priv->ndev->type == ARPHRD_IEEE80211_PRISM) {
		struct avs_80211_1_header *avs;
		/* extract the relevant data from the header */
		u32 clock = le32_to_cpu(hdr->clock);
		u8 rate = hdr->rate;
		u16 freq = le16_to_cpu(hdr->freq);
		u8 rssi = hdr->rssi;

		skb_pull(*skb, sizeof (struct rfmon_header));

		if (skb_headroom(*skb) < sizeof (struct avs_80211_1_header)) {
			struct sk_buff *newskb = skb_copy_expand(*skb,
								 sizeof (struct
									 avs_80211_1_header),
								 0, GFP_ATOMIC);
			if (newskb) {
				dev_kfree_skb_irq(*skb);
				*skb = newskb;
			} else
				return -1;
			/* This behavior is not very subtile... */
		}

		/* make room for the new header and fill it. */
		avs =
		    (struct avs_80211_1_header *) skb_push(*skb,
							   sizeof (struct
								   avs_80211_1_header));

		avs->version = cpu_to_be32(P80211CAPTURE_VERSION);
		avs->length = cpu_to_be32(sizeof (struct avs_80211_1_header));
		avs->mactime = cpu_to_be64(clock);
		avs->hosttime = cpu_to_be64(jiffies);
		avs->phytype = cpu_to_be32(6);	/*OFDM: 6 for (g), 8 for (a) */
		avs->channel = cpu_to_be32(channel_of_freq(freq));
		avs->datarate = cpu_to_be32(rate * 5);
		avs->antenna = cpu_to_be32(0);	/*unknown */
		avs->priority = cpu_to_be32(0);	/*unknown */
		avs->ssi_type = cpu_to_be32(3);	/*2: dBm, 3: raw RSSI */
		avs->ssi_signal = cpu_to_be32(rssi & 0x7f);
		avs->ssi_noise = cpu_to_be32(priv->local_iwstatistics.qual.noise);	/*better than 'undefined', I assume */
		avs->preamble = cpu_to_be32(0);	/*unknown */
		avs->encoding = cpu_to_be32(0);	/*unknown */
	} else
		skb_pull(*skb, sizeof (struct rfmon_header));

	(*skb)->protocol = htons(ETH_P_802_2);
	skb_reset_mac_header(*skb);
	(*skb)->pkt_type = PACKET_OTHERHOST;

	return 0;
}