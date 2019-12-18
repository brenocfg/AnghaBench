#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tip ;
struct sk_buff {struct net_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct port_info {scalar_t__ iscsi_ipv4addr; TYPE_1__ iscsic; } ;
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct arphdr {scalar_t__ ar_op; } ;
typedef  int /*<<< orphan*/  sip ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REPLY ; 
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 struct arphdr* arp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  arp_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct net_device*,scalar_t__,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static void cxgb3_arp_process(struct port_info *pi, struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	struct arphdr *arp;
	unsigned char *arp_ptr;
	unsigned char *sha;
	__be32 sip, tip;

	if (!dev)
		return;

	skb_reset_network_header(skb);
	arp = arp_hdr(skb);

	if (arp->ar_op != htons(ARPOP_REQUEST))
		return;

	arp_ptr = (unsigned char *)(arp + 1);
	sha = arp_ptr;
	arp_ptr += dev->addr_len;
	memcpy(&sip, arp_ptr, sizeof(sip));
	arp_ptr += sizeof(sip);
	arp_ptr += dev->addr_len;
	memcpy(&tip, arp_ptr, sizeof(tip));

	if (tip != pi->iscsi_ipv4addr)
		return;

	arp_send(ARPOP_REPLY, ETH_P_ARP, sip, dev, tip, sha,
		 pi->iscsic.mac_addr, sha);

}