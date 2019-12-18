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
struct sk_buff {int dummy; } ;
struct net_device {void const* dev_addr; int /*<<< orphan*/  addr_len; } ;
struct fcllc {int* protid; int /*<<< orphan*/  ethertype; int /*<<< orphan*/  llc; int /*<<< orphan*/  ssap; int /*<<< orphan*/  dsap; } ;
struct fch_hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 unsigned short ETH_P_ARP ; 
 unsigned short ETH_P_IP ; 
 int /*<<< orphan*/  EXTENDED_SAP ; 
 int /*<<< orphan*/  UI_CMD ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int fc_header(struct sk_buff *skb, struct net_device *dev,
		     unsigned short type,
		     const void *daddr, const void *saddr, unsigned len)
{
	struct fch_hdr *fch;
	int hdr_len;

	/*
	 * Add the 802.2 SNAP header if IP as the IPv4 code calls
	 * dev->hard_header directly.
	 */
	if (type == ETH_P_IP || type == ETH_P_ARP)
	{
		struct fcllc *fcllc;

		hdr_len = sizeof(struct fch_hdr) + sizeof(struct fcllc);
		fch = (struct fch_hdr *)skb_push(skb, hdr_len);
		fcllc = (struct fcllc *)(fch+1);
		fcllc->dsap = fcllc->ssap = EXTENDED_SAP;
		fcllc->llc = UI_CMD;
		fcllc->protid[0] = fcllc->protid[1] = fcllc->protid[2] = 0x00;
		fcllc->ethertype = htons(type);
	}
	else
	{
		hdr_len = sizeof(struct fch_hdr);
		fch = (struct fch_hdr *)skb_push(skb, hdr_len);
	}

	if(saddr)
		memcpy(fch->saddr,saddr,dev->addr_len);
	else
		memcpy(fch->saddr,dev->dev_addr,dev->addr_len);

	if(daddr)
	{
		memcpy(fch->daddr,daddr,dev->addr_len);
		return(hdr_len);
	}
	return -hdr_len;
}