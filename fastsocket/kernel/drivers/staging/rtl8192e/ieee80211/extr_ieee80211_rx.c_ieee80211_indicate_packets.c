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
typedef  size_t u8 ;
typedef  int u16 ;
struct sk_buff {int* data; int len; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  dev; int /*<<< orphan*/  cb; int /*<<< orphan*/  protocol; } ;
struct ieee80211_rxb {size_t nr_subframes; int* src; int* dst; struct sk_buff** subframes; } ;
struct ieee80211_device {int /*<<< orphan*/  last_rx_ps_time; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int ETH_ALEN ; 
 int ETH_P_AARP ; 
 int ETH_P_IPX ; 
 int /*<<< orphan*/  SNAP_SIZE ; 
 int /*<<< orphan*/  bridge_tunnel_header ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int htons (int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct ieee80211_rxb*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rfc1042_header ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

void ieee80211_indicate_packets(struct ieee80211_device *ieee, struct ieee80211_rxb** prxbIndicateArray,u8  index)
{
	u8 i = 0 , j=0;
	u16 ethertype;
//	if(index > 1)
//		IEEE80211_DEBUG(IEEE80211_DL_REORDER,"%s(): hahahahhhh, We indicate packet from reorder list, index is %u\n",__FUNCTION__,index);
	for(j = 0; j<index; j++)
	{
//added by amy for reorder
		struct ieee80211_rxb* prxb = prxbIndicateArray[j];
		for(i = 0; i<prxb->nr_subframes; i++) {
			struct sk_buff *sub_skb = prxb->subframes[i];

		/* convert hdr + possible LLC headers into Ethernet header */
			ethertype = (sub_skb->data[6] << 8) | sub_skb->data[7];
			if (sub_skb->len >= 8 &&
				((memcmp(sub_skb->data, rfc1042_header, SNAP_SIZE) == 0 &&
				  ethertype != ETH_P_AARP && ethertype != ETH_P_IPX) ||
				 memcmp(sub_skb->data, bridge_tunnel_header, SNAP_SIZE) == 0)) {
			/* remove RFC1042 or Bridge-Tunnel encapsulation and
			 * replace EtherType */
				skb_pull(sub_skb, SNAP_SIZE);
				memcpy(skb_push(sub_skb, ETH_ALEN), prxb->src, ETH_ALEN);
				memcpy(skb_push(sub_skb, ETH_ALEN), prxb->dst, ETH_ALEN);
			} else {
				u16 len;
			/* Leave Ethernet header part of hdr and full payload */
				len = htons(sub_skb->len);
				memcpy(skb_push(sub_skb, 2), &len, 2);
				memcpy(skb_push(sub_skb, ETH_ALEN), prxb->src, ETH_ALEN);
				memcpy(skb_push(sub_skb, ETH_ALEN), prxb->dst, ETH_ALEN);
			}
			//stats->rx_packets++;
			//stats->rx_bytes += sub_skb->len;

		/* Indicat the packets to upper layer */
			if (sub_skb) {
				//printk("0skb_len(%d)\n", skb->len);
				sub_skb->protocol = eth_type_trans(sub_skb, ieee->dev);
				memset(sub_skb->cb, 0, sizeof(sub_skb->cb));
				sub_skb->dev = ieee->dev;
				sub_skb->ip_summed = CHECKSUM_NONE; /* 802.11 crc not sufficient */
				//skb->ip_summed = CHECKSUM_UNNECESSARY; /* 802.11 crc not sufficient */
				ieee->last_rx_ps_time = jiffies;
				//printk("1skb_len(%d)\n", skb->len);
				netif_rx(sub_skb);
			}
		}
		kfree(prxb);
		prxb = NULL;
	}
}