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
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned short ETH_P_AX25 ; 
 int ax25_hard_header (struct sk_buff*,struct net_device*,unsigned short,void const*,void const*,unsigned int) ; 

__attribute__((used)) static int sp_header(struct sk_buff *skb, struct net_device *dev,
		     unsigned short type, const void *daddr,
		     const void *saddr, unsigned len)
{
#ifdef CONFIG_INET
	if (type != ETH_P_AX25)
		return ax25_hard_header(skb, dev, type, daddr, saddr, len);
#endif
	return 0;
}