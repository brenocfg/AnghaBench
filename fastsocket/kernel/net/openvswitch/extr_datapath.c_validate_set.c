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
struct TYPE_4__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  frag; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct sw_flow_key {TYPE_2__ ip; TYPE_1__ eth; } ;
struct sw_flow_actions {int dummy; } ;
struct ovs_key_ipv6 {int /*<<< orphan*/  ipv6_label; int /*<<< orphan*/  ipv6_frag; int /*<<< orphan*/  ipv6_proto; } ;
struct ovs_key_ipv4 {int /*<<< orphan*/  ipv4_frag; int /*<<< orphan*/  ipv4_proto; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
#define  OVS_KEY_ATTR_ETHERNET 135 
#define  OVS_KEY_ATTR_IPV4 134 
#define  OVS_KEY_ATTR_IPV6 133 
 int OVS_KEY_ATTR_MAX ; 
#define  OVS_KEY_ATTR_PRIORITY 132 
#define  OVS_KEY_ATTR_SKB_MARK 131 
#define  OVS_KEY_ATTR_TCP 130 
#define  OVS_KEY_ATTR_TUNNEL 129 
#define  OVS_KEY_ATTR_UDP 128 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 void* nla_data (struct nlattr const*) ; 
 int nla_len (struct nlattr const*) ; 
 scalar_t__ nla_total_size (int) ; 
 int nla_type (struct nlattr const*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int* ovs_key_lens ; 
 int validate_and_copy_set_tun (struct nlattr const*,struct sw_flow_actions**) ; 
 int validate_tp_port (struct sw_flow_key const*) ; 

__attribute__((used)) static int validate_set(const struct nlattr *a,
			const struct sw_flow_key *flow_key,
			struct sw_flow_actions **sfa,
			bool *set_tun)
{
	const struct nlattr *ovs_key = nla_data(a);
	int key_type = nla_type(ovs_key);

	/* There can be only one key in a action */
	if (nla_total_size(nla_len(ovs_key)) != nla_len(a))
		return -EINVAL;

	if (key_type > OVS_KEY_ATTR_MAX ||
	   (ovs_key_lens[key_type] != nla_len(ovs_key) &&
	    ovs_key_lens[key_type] != -1))
		return -EINVAL;

	switch (key_type) {
	const struct ovs_key_ipv4 *ipv4_key;
	const struct ovs_key_ipv6 *ipv6_key;
	int err;

	case OVS_KEY_ATTR_PRIORITY:
	case OVS_KEY_ATTR_SKB_MARK:
	case OVS_KEY_ATTR_ETHERNET:
		break;

	case OVS_KEY_ATTR_TUNNEL:
		*set_tun = true;
		err = validate_and_copy_set_tun(a, sfa);
		if (err)
			return err;
		break;

	case OVS_KEY_ATTR_IPV4:
		if (flow_key->eth.type != htons(ETH_P_IP))
			return -EINVAL;

		if (!flow_key->ip.proto)
			return -EINVAL;

		ipv4_key = nla_data(ovs_key);
		if (ipv4_key->ipv4_proto != flow_key->ip.proto)
			return -EINVAL;

		if (ipv4_key->ipv4_frag != flow_key->ip.frag)
			return -EINVAL;

		break;

	case OVS_KEY_ATTR_IPV6:
		if (flow_key->eth.type != htons(ETH_P_IPV6))
			return -EINVAL;

		if (!flow_key->ip.proto)
			return -EINVAL;

		ipv6_key = nla_data(ovs_key);
		if (ipv6_key->ipv6_proto != flow_key->ip.proto)
			return -EINVAL;

		if (ipv6_key->ipv6_frag != flow_key->ip.frag)
			return -EINVAL;

		if (ntohl(ipv6_key->ipv6_label) & 0xFFF00000)
			return -EINVAL;

		break;

	case OVS_KEY_ATTR_TCP:
		if (flow_key->ip.proto != IPPROTO_TCP)
			return -EINVAL;

		return validate_tp_port(flow_key);

	case OVS_KEY_ATTR_UDP:
		if (flow_key->ip.proto != IPPROTO_UDP)
			return -EINVAL;

		return validate_tp_port(flow_key);

	default:
		return -EINVAL;
	}

	return 0;
}