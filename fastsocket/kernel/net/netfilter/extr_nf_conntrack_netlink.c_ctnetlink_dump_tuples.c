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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  protonum; } ;
struct TYPE_3__ {int /*<<< orphan*/  l3num; } ;
struct nf_conntrack_tuple {TYPE_2__ dst; TYPE_1__ src; } ;
struct nf_conntrack_l4proto {int dummy; } ;
struct nf_conntrack_l3proto {int dummy; } ;

/* Variables and functions */
 struct nf_conntrack_l3proto* __nf_ct_l3proto_find (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ctnetlink_dump_tuples_ip (struct sk_buff*,struct nf_conntrack_tuple const*,struct nf_conntrack_l3proto*) ; 
 int ctnetlink_dump_tuples_proto (struct sk_buff*,struct nf_conntrack_tuple const*,struct nf_conntrack_l4proto*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
ctnetlink_dump_tuples(struct sk_buff *skb,
		      const struct nf_conntrack_tuple *tuple)
{
	int ret;
	struct nf_conntrack_l3proto *l3proto;
	struct nf_conntrack_l4proto *l4proto;

	l3proto = __nf_ct_l3proto_find(tuple->src.l3num);
	ret = ctnetlink_dump_tuples_ip(skb, tuple, l3proto);

	if (unlikely(ret < 0))
		return ret;

	l4proto = __nf_ct_l4proto_find(tuple->src.l3num, tuple->dst.protonum);
	ret = ctnetlink_dump_tuples_proto(skb, tuple, l4proto);

	return ret;
}