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
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 int eth_header (struct sk_buff*,struct net_device*,unsigned short,void const*,void const*,unsigned int) ; 
 int /*<<< orphan*/  plip_rewrite_address (struct net_device*,struct ethhdr*) ; 

__attribute__((used)) static int
plip_hard_header(struct sk_buff *skb, struct net_device *dev,
		 unsigned short type, const void *daddr,
		 const void *saddr, unsigned len)
{
	int ret;

	ret = eth_header(skb, dev, type, daddr, saddr, len);
	if (ret >= 0)
		plip_rewrite_address (dev, (struct ethhdr *)skb->data);

	return ret;
}