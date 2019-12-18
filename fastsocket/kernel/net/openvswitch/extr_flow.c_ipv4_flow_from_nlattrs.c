#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {void* dst; void* src; } ;
struct TYPE_7__ {TYPE_2__ tp; } ;
struct TYPE_5__ {int proto; } ;
struct sw_flow_key {TYPE_3__ ipv4; TYPE_1__ ip; } ;
struct ovs_key_udp {void* udp_dst; void* udp_src; } ;
struct ovs_key_tcp {void* tcp_dst; void* tcp_src; } ;
struct ovs_key_icmp {int /*<<< orphan*/  icmp_code; int /*<<< orphan*/  icmp_type; } ;
struct nlattr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IPPROTO_ICMP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int OVS_KEY_ATTR_ICMP ; 
 int OVS_KEY_ATTR_TCP ; 
 int OVS_KEY_ATTR_UDP ; 
 int SW_FLOW_KEY_OFFSET (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 TYPE_4__ ipv4 ; 
 void* nla_data (struct nlattr const*) ; 

__attribute__((used)) static int ipv4_flow_from_nlattrs(struct sw_flow_key *swkey, int *key_len,
				  const struct nlattr *a[], u32 *attrs)
{
	const struct ovs_key_icmp *icmp_key;
	const struct ovs_key_tcp *tcp_key;
	const struct ovs_key_udp *udp_key;

	switch (swkey->ip.proto) {
	case IPPROTO_TCP:
		if (!(*attrs & (1 << OVS_KEY_ATTR_TCP)))
			return -EINVAL;
		*attrs &= ~(1 << OVS_KEY_ATTR_TCP);

		*key_len = SW_FLOW_KEY_OFFSET(ipv4.tp);
		tcp_key = nla_data(a[OVS_KEY_ATTR_TCP]);
		swkey->ipv4.tp.src = tcp_key->tcp_src;
		swkey->ipv4.tp.dst = tcp_key->tcp_dst;
		break;

	case IPPROTO_UDP:
		if (!(*attrs & (1 << OVS_KEY_ATTR_UDP)))
			return -EINVAL;
		*attrs &= ~(1 << OVS_KEY_ATTR_UDP);

		*key_len = SW_FLOW_KEY_OFFSET(ipv4.tp);
		udp_key = nla_data(a[OVS_KEY_ATTR_UDP]);
		swkey->ipv4.tp.src = udp_key->udp_src;
		swkey->ipv4.tp.dst = udp_key->udp_dst;
		break;

	case IPPROTO_ICMP:
		if (!(*attrs & (1 << OVS_KEY_ATTR_ICMP)))
			return -EINVAL;
		*attrs &= ~(1 << OVS_KEY_ATTR_ICMP);

		*key_len = SW_FLOW_KEY_OFFSET(ipv4.tp);
		icmp_key = nla_data(a[OVS_KEY_ATTR_ICMP]);
		swkey->ipv4.tp.src = htons(icmp_key->icmp_type);
		swkey->ipv4.tp.dst = htons(icmp_key->icmp_code);
		break;
	}

	return 0;
}