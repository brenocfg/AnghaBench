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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_ACTION_ATTR_SET ; 
#define  OVS_KEY_ATTR_IPV4_TUNNEL 128 
 struct nlattr* nla_data (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlattr const*) ; 
 int nla_type (struct nlattr const*) ; 
 int ovs_ipv4_tun_to_nlattr (struct sk_buff*,struct nlattr*) ; 

__attribute__((used)) static int set_action_to_attr(const struct nlattr *a, struct sk_buff *skb)
{
	const struct nlattr *ovs_key = nla_data(a);
	int key_type = nla_type(ovs_key);
	struct nlattr *start;
	int err;

	switch (key_type) {
	case OVS_KEY_ATTR_IPV4_TUNNEL:
		start = nla_nest_start(skb, OVS_ACTION_ATTR_SET);
		if (!start)
			return -EMSGSIZE;

		err = ovs_ipv4_tun_to_nlattr(skb, nla_data(ovs_key));
		if (err)
			return err;
		nla_nest_end(skb, start);
		break;
	default:
		if (nla_put(skb, OVS_ACTION_ATTR_SET, nla_len(a), ovs_key))
			return -EMSGSIZE;
		break;
	}

	return 0;
}