#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {int flags; int /*<<< orphan*/ * dev_addr; TYPE_2__ stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  sequence; } ;
struct arcnet_local {TYPE_3__ rfc1201; } ;
struct TYPE_8__ {scalar_t__ dest; int /*<<< orphan*/  source; } ;
struct arc_rfc1201 {scalar_t__ split_flag; int /*<<< orphan*/  sequence; int /*<<< orphan*/  proto; } ;
struct TYPE_5__ {struct arc_rfc1201 rfc1201; } ;
struct archdr {TYPE_4__ hard; TYPE_1__ soft; } ;

/* Variables and functions */
 int ARC_HDR_SIZE ; 
 int /*<<< orphan*/  ARC_P_ARP ; 
 int /*<<< orphan*/  ARC_P_ATALK ; 
 int /*<<< orphan*/  ARC_P_IP ; 
 int /*<<< orphan*/  ARC_P_IPV6 ; 
 int /*<<< orphan*/  ARC_P_IPX ; 
 int /*<<< orphan*/  ARC_P_RARP ; 
 int /*<<< orphan*/  BUGMSG (int /*<<< orphan*/ ,char*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  D_NORMAL ; 
#define  ETH_P_802_2 135 
#define  ETH_P_802_3 134 
#define  ETH_P_ARP 133 
#define  ETH_P_ATALK 132 
#define  ETH_P_IP 131 
#define  ETH_P_IPV6 130 
#define  ETH_P_IPX 129 
#define  ETH_P_RARP 128 
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int RFC1201_HDR_SIZE ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct arcnet_local* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int build_header(struct sk_buff *skb, struct net_device *dev,
			unsigned short type, uint8_t daddr)
{
	struct arcnet_local *lp = netdev_priv(dev);
	int hdr_size = ARC_HDR_SIZE + RFC1201_HDR_SIZE;
	struct archdr *pkt = (struct archdr *) skb_push(skb, hdr_size);
	struct arc_rfc1201 *soft = &pkt->soft.rfc1201;

	/* set the protocol ID according to RFC1201 */
	switch (type) {
	case ETH_P_IP:
		soft->proto = ARC_P_IP;
		break;
	case ETH_P_IPV6:
		soft->proto = ARC_P_IPV6;
		break;
	case ETH_P_ARP:
		soft->proto = ARC_P_ARP;
		break;
	case ETH_P_RARP:
		soft->proto = ARC_P_RARP;
		break;
	case ETH_P_IPX:
	case ETH_P_802_3:
	case ETH_P_802_2:
		soft->proto = ARC_P_IPX;
		break;
	case ETH_P_ATALK:
		soft->proto = ARC_P_ATALK;
		break;
	default:
		BUGMSG(D_NORMAL, "RFC1201: I don't understand protocol %d (%Xh)\n",
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

	soft->sequence = htons(lp->rfc1201.sequence++);
	soft->split_flag = 0;	/* split packets are done elsewhere */

	/* see linux/net/ethernet/eth.c to see where I got the following */

	if (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) {
		/* 
		 * FIXME: fill in the last byte of the dest ipaddr here to better
		 * comply with RFC1051 in "noarp" mode.  For now, always broadcasting
		 * will probably at least get packets sent out :)
		 */
		pkt->hard.dest = 0;
		return hdr_size;
	}
	/* otherwise, drop in the dest address */
	pkt->hard.dest = daddr;
	return hdr_size;
}