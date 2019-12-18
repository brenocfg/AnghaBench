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
struct trllc {scalar_t__ dsap; scalar_t__ ethertype; } ;
struct trh_hdr {int* saddr; int* daddr; int /*<<< orphan*/  rcf; } ;
struct sk_buff {scalar_t__ pkt_type; scalar_t__ data; struct net_device* dev; } ;
struct net_device {int flags; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ETH_P_TR_802_2 ; 
 scalar_t__ EXTENDED_SAP ; 
 int IFF_PROMISC ; 
 scalar_t__ PACKET_BROADCAST ; 
 scalar_t__ PACKET_MULTICAST ; 
 scalar_t__ PACKET_OTHERHOST ; 
 int /*<<< orphan*/  TR_ALEN ; 
 int TR_MAXRIFLEN ; 
 int TR_RCF_LEN_MASK ; 
 int TR_RII ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  tr_add_rif_info (struct trh_hdr*,struct net_device*) ; 
 struct trh_hdr* tr_hdr (struct sk_buff*) ; 

__be16 tr_type_trans(struct sk_buff *skb, struct net_device *dev)
{

	struct trh_hdr *trh;
	struct trllc *trllc;
	unsigned riflen=0;

	skb->dev = dev;
	skb_reset_mac_header(skb);
	trh = tr_hdr(skb);

	if(trh->saddr[0] & TR_RII)
		riflen = (ntohs(trh->rcf) & TR_RCF_LEN_MASK) >> 8;

	trllc = (struct trllc *)(skb->data+sizeof(struct trh_hdr)-TR_MAXRIFLEN+riflen);

	skb_pull(skb,sizeof(struct trh_hdr)-TR_MAXRIFLEN+riflen);

	if(*trh->daddr & 0x80)
	{
		if(!memcmp(trh->daddr,dev->broadcast,TR_ALEN))
			skb->pkt_type=PACKET_BROADCAST;
		else
			skb->pkt_type=PACKET_MULTICAST;
	}
	else if ( (trh->daddr[0] & 0x01) && (trh->daddr[1] & 0x00) && (trh->daddr[2] & 0x5E))
	{
		skb->pkt_type=PACKET_MULTICAST;
	}
	else if(dev->flags & IFF_PROMISC)
	{
		if(memcmp(trh->daddr, dev->dev_addr, TR_ALEN))
			skb->pkt_type=PACKET_OTHERHOST;
	}

	if ((skb->pkt_type != PACKET_BROADCAST) &&
	    (skb->pkt_type != PACKET_MULTICAST))
		tr_add_rif_info(trh,dev) ;

	/*
	 * Strip the SNAP header from ARP packets since we don't
	 * pass them through to the 802.2/SNAP layers.
	 */

	if (trllc->dsap == EXTENDED_SAP &&
	    (trllc->ethertype == htons(ETH_P_IP) ||
	     trllc->ethertype == htons(ETH_P_IPV6) ||
	     trllc->ethertype == htons(ETH_P_ARP)))
	{
		skb_pull(skb, sizeof(struct trllc));
		return trllc->ethertype;
	}

	return htons(ETH_P_TR_802_2);
}