#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_2__* ip_hdr (struct sk_buff const*) ; 
 int ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff const*) ; 
 int xt_cluster_ipv6_is_multicast (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
xt_cluster_is_multicast_addr(const struct sk_buff *skb, u_int8_t family)
{
	bool is_multicast = false;

	switch(family) {
	case NFPROTO_IPV4:
		is_multicast = ipv4_is_multicast(ip_hdr(skb)->daddr);
		break;
	case NFPROTO_IPV6:
		is_multicast =
			xt_cluster_ipv6_is_multicast(&ipv6_hdr(skb)->daddr);
		break;
	default:
		WARN_ON(1);
		break;
	}
	return is_multicast;
}