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
struct sk_buff {unsigned char* data; int /*<<< orphan*/  pkt_type; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; } ;
struct eth1394hdr {int* h_dest; int /*<<< orphan*/  h_proto; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH1394_HLEN ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  ETH_P_802_3 ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_MULTICAST ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 struct eth1394hdr* eth1394_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static __be16 ether1394_type_trans(struct sk_buff *skb, struct net_device *dev)
{
	struct eth1394hdr *eth;
	unsigned char *rawp;

	skb_reset_mac_header(skb);
	skb_pull(skb, ETH1394_HLEN);
	eth = eth1394_hdr(skb);

	if (*eth->h_dest & 1) {
		if (memcmp(eth->h_dest, dev->broadcast, dev->addr_len) == 0)
			skb->pkt_type = PACKET_BROADCAST;
#if 0
		else
			skb->pkt_type = PACKET_MULTICAST;
#endif
	} else {
		if (memcmp(eth->h_dest, dev->dev_addr, dev->addr_len))
			skb->pkt_type = PACKET_OTHERHOST;
	}

	if (ntohs(eth->h_proto) >= 1536)
		return eth->h_proto;

	rawp = skb->data;

	if (*(unsigned short *)rawp == 0xFFFF)
		return htons(ETH_P_802_3);

	return htons(ETH_P_802_2);
}