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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int hdrlen; int /*<<< orphan*/  nexthdr; } ;
struct rt0_hdr {TYPE_1__ rt_hdr; struct rt0_hdr* addr; } ;
struct ipv6_rt_hdr {int dummy; } ;
struct in6_addr {TYPE_1__ rt_hdr; struct in6_addr* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEXTHDR_ROUTING ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct rt0_hdr*,struct rt0_hdr*) ; 
 int /*<<< orphan*/  memcpy (struct rt0_hdr*,struct rt0_hdr*,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void ipv6_push_rthdr(struct sk_buff *skb, u8 *proto,
			    struct ipv6_rt_hdr *opt,
			    struct in6_addr **addr_p)
{
	struct rt0_hdr *phdr, *ihdr;
	int hops;

	ihdr = (struct rt0_hdr *) opt;

	phdr = (struct rt0_hdr *) skb_push(skb, (ihdr->rt_hdr.hdrlen + 1) << 3);
	memcpy(phdr, ihdr, sizeof(struct rt0_hdr));

	hops = ihdr->rt_hdr.hdrlen >> 1;

	if (hops > 1)
		memcpy(phdr->addr, ihdr->addr + 1,
		       (hops - 1) * sizeof(struct in6_addr));

	ipv6_addr_copy(phdr->addr + (hops - 1), *addr_p);
	*addr_p = ihdr->addr;

	phdr->rt_hdr.nexthdr = *proto;
	*proto = NEXTHDR_ROUTING;
}