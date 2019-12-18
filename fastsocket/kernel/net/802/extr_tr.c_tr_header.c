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
struct trllc {int* protid; int /*<<< orphan*/  ethertype; int /*<<< orphan*/  llc; int /*<<< orphan*/  ssap; int /*<<< orphan*/  dsap; } ;
struct trh_hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  fc; int /*<<< orphan*/  ac; } ;
struct sk_buff {int dummy; } ;
struct net_device {void const* dev_addr; int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC ; 
 unsigned short ETH_P_ARP ; 
 unsigned short ETH_P_IP ; 
 unsigned short ETH_P_IPV6 ; 
 int /*<<< orphan*/  EXTENDED_SAP ; 
 int /*<<< orphan*/  LLC_FRAME ; 
 int /*<<< orphan*/  UI_CMD ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  tr_source_route (struct sk_buff*,struct trh_hdr*,struct net_device*) ; 

__attribute__((used)) static int tr_header(struct sk_buff *skb, struct net_device *dev,
		     unsigned short type,
		     const void *daddr, const void *saddr, unsigned len)
{
	struct trh_hdr *trh;
	int hdr_len;

	/*
	 * Add the 802.2 SNAP header if IP as the IPv4/IPv6 code calls
	 * dev->hard_header directly.
	 */
	if (type == ETH_P_IP || type == ETH_P_IPV6 || type == ETH_P_ARP)
	{
		struct trllc *trllc;

		hdr_len = sizeof(struct trh_hdr) + sizeof(struct trllc);
		trh = (struct trh_hdr *)skb_push(skb, hdr_len);
		trllc = (struct trllc *)(trh+1);
		trllc->dsap = trllc->ssap = EXTENDED_SAP;
		trllc->llc = UI_CMD;
		trllc->protid[0] = trllc->protid[1] = trllc->protid[2] = 0x00;
		trllc->ethertype = htons(type);
	}
	else
	{
		hdr_len = sizeof(struct trh_hdr);
		trh = (struct trh_hdr *)skb_push(skb, hdr_len);
	}

	trh->ac=AC;
	trh->fc=LLC_FRAME;

	if(saddr)
		memcpy(trh->saddr,saddr,dev->addr_len);
	else
		memcpy(trh->saddr,dev->dev_addr,dev->addr_len);

	/*
	 *	Build the destination and then source route the frame
	 */

	if(daddr)
	{
		memcpy(trh->daddr,daddr,dev->addr_len);
		tr_source_route(skb, trh, dev);
		return(hdr_len);
	}

	return -hdr_len;
}