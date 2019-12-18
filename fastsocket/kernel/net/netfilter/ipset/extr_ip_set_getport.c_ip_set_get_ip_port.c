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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int ip_set_get_ip4_port (struct sk_buff const*,int,int /*<<< orphan*/ *,int*) ; 
 int ip_set_get_ip6_port (struct sk_buff const*,int,int /*<<< orphan*/ *,int*) ; 

bool
ip_set_get_ip_port(const struct sk_buff *skb, u8 pf, bool src, __be16 *port)
{
	bool ret;
	u8 proto;

	switch (pf) {
	case AF_INET:
		ret = ip_set_get_ip4_port(skb, src, port, &proto);
		break;
	case AF_INET6:
		ret = ip_set_get_ip6_port(skb, src, port, &proto);
		break;
	default:
		return false;
	}
	if (!ret)
		return ret;
	switch (proto) {
	case IPPROTO_TCP:
	case IPPROTO_UDP:
		return true;
	default:
		return false;
	}
}