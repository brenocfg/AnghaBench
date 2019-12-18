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
struct TYPE_6__ {int /*<<< orphan*/ * tll; int /*<<< orphan*/ * sll; int /*<<< orphan*/  target; } ;
struct TYPE_5__ {void* dst; void* src; } ;
struct TYPE_7__ {TYPE_2__ nd; TYPE_1__ tp; } ;
struct sw_flow_key {TYPE_3__ ipv6; } ;
struct sk_buff {int len; } ;
struct nd_opt_hdr {int nd_opt_len; scalar_t__ nd_opt_type; } ;
struct nd_msg {int /*<<< orphan*/ * opt; int /*<<< orphan*/  target; } ;
struct icmp6hdr {scalar_t__ icmp6_type; scalar_t__ icmp6_code; } ;
struct TYPE_8__ {int /*<<< orphan*/  nd; int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NDISC_NEIGHBOUR_ADVERTISEMENT ; 
 scalar_t__ NDISC_NEIGHBOUR_SOLICITATION ; 
 scalar_t__ ND_OPT_SOURCE_LL_ADDR ; 
 scalar_t__ ND_OPT_TARGET_LL_ADDR ; 
 int SW_FLOW_KEY_OFFSET (int /*<<< orphan*/ ) ; 
 void* htons (scalar_t__) ; 
 struct icmp6hdr* icmp6_hdr (struct sk_buff*) ; 
 TYPE_4__ ipv6 ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int skb_linearize (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int parse_icmpv6(struct sk_buff *skb, struct sw_flow_key *key,
			int *key_lenp, int nh_len)
{
	struct icmp6hdr *icmp = icmp6_hdr(skb);
	int error = 0;
	int key_len;

	/* The ICMPv6 type and code fields use the 16-bit transport port
	 * fields, so we need to store them in 16-bit network byte order.
	 */
	key->ipv6.tp.src = htons(icmp->icmp6_type);
	key->ipv6.tp.dst = htons(icmp->icmp6_code);
	key_len = SW_FLOW_KEY_OFFSET(ipv6.tp);

	if (icmp->icmp6_code == 0 &&
	    (icmp->icmp6_type == NDISC_NEIGHBOUR_SOLICITATION ||
	     icmp->icmp6_type == NDISC_NEIGHBOUR_ADVERTISEMENT)) {
		int icmp_len = skb->len - skb_transport_offset(skb);
		struct nd_msg *nd;
		int offset;

		key_len = SW_FLOW_KEY_OFFSET(ipv6.nd);

		/* In order to process neighbor discovery options, we need the
		 * entire packet.
		 */
		if (unlikely(icmp_len < sizeof(*nd)))
			goto out;
		if (unlikely(skb_linearize(skb))) {
			error = -ENOMEM;
			goto out;
		}

		nd = (struct nd_msg *)skb_transport_header(skb);
		key->ipv6.nd.target = nd->target;
		key_len = SW_FLOW_KEY_OFFSET(ipv6.nd);

		icmp_len -= sizeof(*nd);
		offset = 0;
		while (icmp_len >= 8) {
			struct nd_opt_hdr *nd_opt =
				 (struct nd_opt_hdr *)(nd->opt + offset);
			int opt_len = nd_opt->nd_opt_len * 8;

			if (unlikely(!opt_len || opt_len > icmp_len))
				goto invalid;

			/* Store the link layer address if the appropriate
			 * option is provided.  It is considered an error if
			 * the same link layer option is specified twice.
			 */
			if (nd_opt->nd_opt_type == ND_OPT_SOURCE_LL_ADDR
			    && opt_len == 8) {
				if (unlikely(!is_zero_ether_addr(key->ipv6.nd.sll)))
					goto invalid;
				memcpy(key->ipv6.nd.sll,
				    &nd->opt[offset+sizeof(*nd_opt)], ETH_ALEN);
			} else if (nd_opt->nd_opt_type == ND_OPT_TARGET_LL_ADDR
				   && opt_len == 8) {
				if (unlikely(!is_zero_ether_addr(key->ipv6.nd.tll)))
					goto invalid;
				memcpy(key->ipv6.nd.tll,
				    &nd->opt[offset+sizeof(*nd_opt)], ETH_ALEN);
			}

			icmp_len -= opt_len;
			offset += opt_len;
		}
	}

	goto out;

invalid:
	memset(&key->ipv6.nd.target, 0, sizeof(key->ipv6.nd.target));
	memset(key->ipv6.nd.sll, 0, sizeof(key->ipv6.nd.sll));
	memset(key->ipv6.nd.tll, 0, sizeof(key->ipv6.nd.tll));

out:
	*key_lenp = key_len;
	return error;
}