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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dir; int /*<<< orphan*/  protonum; } ;
struct TYPE_3__ {int /*<<< orphan*/  l3num; } ;
struct nf_conntrack_tuple {TYPE_2__ dst; TYPE_1__ src; } ;
struct nf_conntrack_l4proto {int (* pkt_to_tuple ) (struct sk_buff const*,unsigned int,struct nf_conntrack_tuple*) ;} ;
struct nf_conntrack_l3proto {scalar_t__ (* pkt_to_tuple ) (struct sk_buff const*,unsigned int,struct nf_conntrack_tuple*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  memset (struct nf_conntrack_tuple*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct sk_buff const*,unsigned int,struct nf_conntrack_tuple*) ; 
 int stub2 (struct sk_buff const*,unsigned int,struct nf_conntrack_tuple*) ; 

bool
nf_ct_get_tuple(const struct sk_buff *skb,
		unsigned int nhoff,
		unsigned int dataoff,
		u_int16_t l3num,
		u_int8_t protonum,
		struct nf_conntrack_tuple *tuple,
		const struct nf_conntrack_l3proto *l3proto,
		const struct nf_conntrack_l4proto *l4proto)
{
	memset(tuple, 0, sizeof(*tuple));

	tuple->src.l3num = l3num;
	if (l3proto->pkt_to_tuple(skb, nhoff, tuple) == 0)
		return false;

	tuple->dst.protonum = protonum;
	tuple->dst.dir = IP_CT_DIR_ORIGINAL;

	return l4proto->pkt_to_tuple(skb, dataoff, tuple);
}