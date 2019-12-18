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

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int ip6_tnl_rcv (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6ip6_dscp_ecn_decapsulate ; 

__attribute__((used)) static int ip6ip6_rcv(struct sk_buff *skb)
{
	return ip6_tnl_rcv(skb, ETH_P_IPV6, IPPROTO_IPV6,
			   ip6ip6_dscp_ecn_decapsulate);
}