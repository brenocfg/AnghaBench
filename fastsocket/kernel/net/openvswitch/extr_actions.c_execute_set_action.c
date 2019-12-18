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
struct sk_buff {void* mark; void* priority; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tun_key; } ;

/* Variables and functions */
 TYPE_1__* OVS_CB (struct sk_buff*) ; 
#define  OVS_KEY_ATTR_ETHERNET 135 
#define  OVS_KEY_ATTR_IPV4 134 
#define  OVS_KEY_ATTR_IPV4_TUNNEL 133 
#define  OVS_KEY_ATTR_IPV6 132 
#define  OVS_KEY_ATTR_PRIORITY 131 
#define  OVS_KEY_ATTR_SKB_MARK 130 
#define  OVS_KEY_ATTR_TCP 129 
#define  OVS_KEY_ATTR_UDP 128 
 int /*<<< orphan*/  nla_data (struct nlattr const*) ; 
 void* nla_get_u32 (struct nlattr const*) ; 
 int nla_type (struct nlattr const*) ; 
 int set_eth_addr (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int set_ipv4 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int set_ipv6 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int set_tcp (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int set_udp (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int execute_set_action(struct sk_buff *skb,
				 const struct nlattr *nested_attr)
{
	int err = 0;

	switch (nla_type(nested_attr)) {
	case OVS_KEY_ATTR_PRIORITY:
		skb->priority = nla_get_u32(nested_attr);
		break;

	case OVS_KEY_ATTR_SKB_MARK:
		skb->mark = nla_get_u32(nested_attr);
		break;

	case OVS_KEY_ATTR_IPV4_TUNNEL:
		OVS_CB(skb)->tun_key = nla_data(nested_attr);
		break;

	case OVS_KEY_ATTR_ETHERNET:
		err = set_eth_addr(skb, nla_data(nested_attr));
		break;

	case OVS_KEY_ATTR_IPV4:
		err = set_ipv4(skb, nla_data(nested_attr));
		break;

	case OVS_KEY_ATTR_IPV6:
		err = set_ipv6(skb, nla_data(nested_attr));
		break;

	case OVS_KEY_ATTR_TCP:
		err = set_tcp(skb, nla_data(nested_attr));
		break;

	case OVS_KEY_ATTR_UDP:
		err = set_udp(skb, nla_data(nested_attr));
		break;
	}

	return err;
}