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
struct net_device {int flags; int hard_header_len; int /*<<< orphan*/  addr_len; } ;
struct eth1394hdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH1394_HLEN ; 
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ether1394_header(struct sk_buff *skb, struct net_device *dev,
			    unsigned short type, const void *daddr,
			    const void *saddr, unsigned len)
{
	struct eth1394hdr *eth =
			(struct eth1394hdr *)skb_push(skb, ETH1394_HLEN);

	eth->h_proto = htons(type);

	if (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) {
		memset(eth->h_dest, 0, dev->addr_len);
		return dev->hard_header_len;
	}

	if (daddr) {
		memcpy(eth->h_dest, daddr, dev->addr_len);
		return dev->hard_header_len;
	}

	return -dev->hard_header_len;
}