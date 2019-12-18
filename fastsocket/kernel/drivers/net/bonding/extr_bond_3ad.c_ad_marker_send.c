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
struct slave {int /*<<< orphan*/  perm_hwaddr; int /*<<< orphan*/  dev; } ;
struct sk_buff {void* protocol; scalar_t__ mac_header; scalar_t__ network_header; int /*<<< orphan*/  dev; } ;
struct port {struct slave* slave; } ;
struct bond_marker {int dummy; } ;
struct TYPE_2__ {void* h_proto; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;
struct bond_marker_header {struct bond_marker marker; TYPE_1__ hdr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ ETH_HLEN ; 
 void* PKT_TYPE_LACPDU ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  lacpdu_mcast_addr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static int ad_marker_send(struct port *port, struct bond_marker *marker)
{
	struct slave *slave = port->slave;
	struct sk_buff *skb;
	struct bond_marker_header *marker_header;
	int length = sizeof(struct bond_marker_header);

	skb = dev_alloc_skb(length + 16);
	if (!skb) {
		return -ENOMEM;
	}

	skb_reserve(skb, 16);

	skb->dev = slave->dev;
	skb_reset_mac_header(skb);
	skb->network_header = skb->mac_header + ETH_HLEN;
	skb->protocol = PKT_TYPE_LACPDU;

	marker_header = (struct bond_marker_header *)skb_put(skb, length);

	memcpy(marker_header->hdr.h_dest, lacpdu_mcast_addr, ETH_ALEN);
	/* Note: source addres is set to be the member's PERMANENT address,
	   because we use it to identify loopback MARKERs in receive. */
	memcpy(marker_header->hdr.h_source, slave->perm_hwaddr, ETH_ALEN);
	marker_header->hdr.h_proto = PKT_TYPE_LACPDU;

	marker_header->marker = *marker; // struct copy

	dev_queue_xmit(skb);

	return 0;
}