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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {int dummy; } ;
struct iphdr {int frag_off; int ihl; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  _iph ;

/* Variables and functions */
 int /*<<< orphan*/  IP_OFFSET ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct iphdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct iphdr*) ; 

__attribute__((used)) static int ipv4_get_l4proto(const struct sk_buff *skb, unsigned int nhoff,
			    unsigned int *dataoff, u_int8_t *protonum)
{
	const struct iphdr *iph;
	struct iphdr _iph;

	iph = skb_header_pointer(skb, nhoff, sizeof(_iph), &_iph);
	if (iph == NULL)
		return -NF_DROP;

	/* Conntrack defragments packets, we might still see fragments
	 * inside ICMP packets though. */
	if (iph->frag_off & htons(IP_OFFSET))
		return -NF_DROP;

	*dataoff = nhoff + (iph->ihl << 2);
	*protonum = iph->protocol;

	return NF_ACCEPT;
}