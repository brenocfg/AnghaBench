#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {TYPE_4__ icmp; } ;
struct TYPE_12__ {TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ icmp; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_6__ dst; TYPE_3__ src; } ;
struct icmp6hdr {int /*<<< orphan*/  icmp6_code; int /*<<< orphan*/  icmp6_identifier; int /*<<< orphan*/  icmp6_type; } ;
typedef  int /*<<< orphan*/  _hdr ;

/* Variables and functions */
 struct icmp6hdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct icmp6hdr*) ; 

__attribute__((used)) static bool icmpv6_pkt_to_tuple(const struct sk_buff *skb,
				unsigned int dataoff,
				struct nf_conntrack_tuple *tuple)
{
	const struct icmp6hdr *hp;
	struct icmp6hdr _hdr;

	hp = skb_header_pointer(skb, dataoff, sizeof(_hdr), &_hdr);
	if (hp == NULL)
		return false;
	tuple->dst.u.icmp.type = hp->icmp6_type;
	tuple->src.u.icmp.id = hp->icmp6_identifier;
	tuple->dst.u.icmp.code = hp->icmp6_code;

	return true;
}