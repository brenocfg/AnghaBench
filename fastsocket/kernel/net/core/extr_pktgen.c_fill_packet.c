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
struct pktgen_dev {int flags; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int F_IPV6 ; 
 struct sk_buff* fill_packet_ipv4 (struct net_device*,struct pktgen_dev*) ; 
 struct sk_buff* fill_packet_ipv6 (struct net_device*,struct pktgen_dev*) ; 

__attribute__((used)) static struct sk_buff *fill_packet(struct net_device *odev,
				   struct pktgen_dev *pkt_dev)
{
	if (pkt_dev->flags & F_IPV6)
		return fill_packet_ipv6(odev, pkt_dev);
	else
		return fill_packet_ipv4(odev, pkt_dev);
}