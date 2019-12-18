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
typedef  scalar_t__ uint8_t ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {int flags; int /*<<< orphan*/ * dev_addr; TYPE_2__ stats; } ;
struct TYPE_6__ {scalar_t__ dest; int /*<<< orphan*/  source; } ;
struct arc_rfc1051 {int /*<<< orphan*/  proto; } ;
struct TYPE_4__ {struct arc_rfc1051 rfc1051; } ;
struct archdr {TYPE_3__ hard; TYPE_1__ soft; } ;

/* Variables and functions */
 int ARC_HDR_SIZE ; 
 int /*<<< orphan*/  ARC_P_ARP_RFC1051 ; 
 int /*<<< orphan*/  ARC_P_IP_RFC1051 ; 
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  D_NORMAL ; 
#define  ETH_P_ARP 129 
#define  ETH_P_IP 128 
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int RFC1051_HDR_SIZE ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int build_header(struct sk_buff *skb, struct net_device *dev,
			unsigned short type, uint8_t daddr)
{
	int hdr_size = ARC_HDR_SIZE + RFC1051_HDR_SIZE;
	struct archdr *pkt = (struct archdr *) skb_push(skb, hdr_size);
	struct arc_rfc1051 *soft = &pkt->soft.rfc1051;

	/* set the protocol ID according to RFC1051 */
	switch (type) {
	case ETH_P_IP:
		soft->proto = ARC_P_IP_RFC1051;
		break;
	case ETH_P_ARP:
		soft->proto = ARC_P_ARP_RFC1051;
		break;
	default:
		BUGMSG(D_NORMAL, "RFC1051: I don't understand protocol %d (%Xh)\n",
		       type, type);
		dev->stats.tx_errors++;
		dev->stats.tx_aborted_errors++;
		return 0;
	}


	/*
	 * Set the source hardware address.
	 *
	 * This is pretty pointless for most purposes, but it can help in
	 * debugging.  ARCnet does not allow us to change the source address in
	 * the actual packet sent)
	 */
	pkt->hard.source = *dev->dev_addr;

	/* see linux/net/ethernet/eth.c to see where I got the following */

	if (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) {
		/* 
		 * FIXME: fill in the last byte of the dest ipaddr here to better
		 * comply with RFC1051 in "noarp" mode.
		 */
		pkt->hard.dest = 0;
		return hdr_size;
	}
	/* otherwise, just fill it in and go! */
	pkt->hard.dest = daddr;

	return hdr_size;	/* success */
}