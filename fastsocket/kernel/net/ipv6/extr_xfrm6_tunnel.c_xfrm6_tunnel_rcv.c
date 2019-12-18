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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ xfrm6_rcv_spi (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm6_tunnel_spi_lookup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xfrm6_tunnel_rcv(struct sk_buff *skb)
{
	struct ipv6hdr *iph = ipv6_hdr(skb);
	__be32 spi;

	spi = xfrm6_tunnel_spi_lookup((xfrm_address_t *)&iph->saddr);
	return xfrm6_rcv_spi(skb, IPPROTO_IPV6, spi) > 0 ? : 0;
}