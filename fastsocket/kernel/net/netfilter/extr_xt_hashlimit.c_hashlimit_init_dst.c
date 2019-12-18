#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {int mode; int /*<<< orphan*/  srcmask; int /*<<< orphan*/  dstmask; } ;
struct xt_hashlimit_htable {int family; TYPE_3__ cfg; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_6__ {void* src; void* dst; } ;
struct dsthash_dst {void* dst_port; void* src_port; TYPE_2__ ip6; TYPE_1__ ip; } ;
typedef  int /*<<< orphan*/  _ports ;
typedef  void* __be16 ;
struct TYPE_10__ {int protocol; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_9__ {int nexthdr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  IPPROTO_DCCP 134 
#define  IPPROTO_SCTP 133 
#define  IPPROTO_TCP 132 
#define  IPPROTO_UDP 131 
#define  IPPROTO_UDPLITE 130 
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int XT_HASHLIMIT_HASH_DIP ; 
 int XT_HASHLIMIT_HASH_DPT ; 
 int XT_HASHLIMIT_HASH_SIP ; 
 int XT_HASHLIMIT_HASH_SPT ; 
 int /*<<< orphan*/  hashlimit_ipv6_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ip_hdr (struct sk_buff const*) ; 
 TYPE_4__* ipv6_hdr (struct sk_buff const*) ; 
 unsigned int ipv6_skip_exthdr (struct sk_buff const*,int,int*) ; 
 void* maskl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct dsthash_dst*,int /*<<< orphan*/ ,int) ; 
 void** skb_header_pointer (struct sk_buff const*,unsigned int,int,void***) ; 

__attribute__((used)) static int
hashlimit_init_dst(const struct xt_hashlimit_htable *hinfo,
		   struct dsthash_dst *dst,
		   const struct sk_buff *skb, unsigned int protoff)
{
	__be16 _ports[2], *ports;
	u8 nexthdr;

	memset(dst, 0, sizeof(*dst));

	switch (hinfo->family) {
	case NFPROTO_IPV4:
		if (hinfo->cfg.mode & XT_HASHLIMIT_HASH_DIP)
			dst->ip.dst = maskl(ip_hdr(skb)->daddr,
			              hinfo->cfg.dstmask);
		if (hinfo->cfg.mode & XT_HASHLIMIT_HASH_SIP)
			dst->ip.src = maskl(ip_hdr(skb)->saddr,
			              hinfo->cfg.srcmask);

		if (!(hinfo->cfg.mode &
		      (XT_HASHLIMIT_HASH_DPT | XT_HASHLIMIT_HASH_SPT)))
			return 0;
		nexthdr = ip_hdr(skb)->protocol;
		break;
#if defined(CONFIG_IP6_NF_IPTABLES) || defined(CONFIG_IP6_NF_IPTABLES_MODULE)
	case NFPROTO_IPV6:
		if (hinfo->cfg.mode & XT_HASHLIMIT_HASH_DIP) {
			memcpy(&dst->ip6.dst, &ipv6_hdr(skb)->daddr,
			       sizeof(dst->ip6.dst));
			hashlimit_ipv6_mask(dst->ip6.dst, hinfo->cfg.dstmask);
		}
		if (hinfo->cfg.mode & XT_HASHLIMIT_HASH_SIP) {
			memcpy(&dst->ip6.src, &ipv6_hdr(skb)->saddr,
			       sizeof(dst->ip6.src));
			hashlimit_ipv6_mask(dst->ip6.src, hinfo->cfg.srcmask);
		}

		if (!(hinfo->cfg.mode &
		      (XT_HASHLIMIT_HASH_DPT | XT_HASHLIMIT_HASH_SPT)))
			return 0;
		nexthdr = ipv6_hdr(skb)->nexthdr;
		protoff = ipv6_skip_exthdr(skb, sizeof(struct ipv6hdr), &nexthdr);
		if ((int)protoff < 0)
			return -1;
		break;
#endif
	default:
		BUG();
		return 0;
	}

	switch (nexthdr) {
	case IPPROTO_TCP:
	case IPPROTO_UDP:
	case IPPROTO_UDPLITE:
	case IPPROTO_SCTP:
	case IPPROTO_DCCP:
		ports = skb_header_pointer(skb, protoff, sizeof(_ports),
					   &_ports);
		break;
	default:
		_ports[0] = _ports[1] = 0;
		ports = _ports;
		break;
	}
	if (!ports)
		return -1;
	if (hinfo->cfg.mode & XT_HASHLIMIT_HASH_SPT)
		dst->src_port = ports[0];
	if (hinfo->cfg.mode & XT_HASHLIMIT_HASH_DPT)
		dst->dst_port = ports[1];
	return 0;
}