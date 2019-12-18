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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tcmsg {scalar_t__ tcm_info; int /*<<< orphan*/  tcm_handle; int /*<<< orphan*/  tcm_parent; int /*<<< orphan*/  tcm_ifindex; scalar_t__ tcm__pad2; scalar_t__ tcm__pad1; int /*<<< orphan*/  tcm_family; } ;
struct sk_buff {int len; } ;
struct nlmsghdr {int nlmsg_len; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc_class_ops {scalar_t__ (* dump ) (struct Qdisc*,unsigned long,struct sk_buff*,struct tcmsg*) ;scalar_t__ (* dump_stats ) (struct Qdisc*,unsigned long,struct gnet_dump*) ;} ;
struct Qdisc {TYPE_1__* ops; int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 struct nlmsghdr* NLMSG_NEW (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCA_KIND ; 
 int /*<<< orphan*/  TCA_STATS ; 
 int /*<<< orphan*/  TCA_STATS2 ; 
 int /*<<< orphan*/  TCA_XSTATS ; 
 scalar_t__ gnet_stats_finish_copy (struct gnet_dump*) ; 
 scalar_t__ gnet_stats_start_copy_compat (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gnet_dump*) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 TYPE_2__* qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_lock (struct Qdisc*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ stub1 (struct Qdisc*,unsigned long,struct sk_buff*,struct tcmsg*) ; 
 scalar_t__ stub2 (struct Qdisc*,unsigned long,struct gnet_dump*) ; 

__attribute__((used)) static int tc_fill_tclass(struct sk_buff *skb, struct Qdisc *q,
			  unsigned long cl,
			  u32 pid, u32 seq, u16 flags, int event)
{
	struct tcmsg *tcm;
	struct nlmsghdr  *nlh;
	unsigned char *b = skb_tail_pointer(skb);
	struct gnet_dump d;
	const struct Qdisc_class_ops *cl_ops = q->ops->cl_ops;

	nlh = NLMSG_NEW(skb, pid, seq, event, sizeof(*tcm), flags);
	tcm = NLMSG_DATA(nlh);
	tcm->tcm_family = AF_UNSPEC;
	tcm->tcm__pad1 = 0;
	tcm->tcm__pad2 = 0;
	tcm->tcm_ifindex = qdisc_dev(q)->ifindex;
	tcm->tcm_parent = q->handle;
	tcm->tcm_handle = q->handle;
	tcm->tcm_info = 0;
	NLA_PUT_STRING(skb, TCA_KIND, q->ops->id);
	if (cl_ops->dump && cl_ops->dump(q, cl, skb, tcm) < 0)
		goto nla_put_failure;

	if (gnet_stats_start_copy_compat(skb, TCA_STATS2, TCA_STATS, TCA_XSTATS,
					 qdisc_root_sleeping_lock(q), &d) < 0)
		goto nla_put_failure;

	if (cl_ops->dump_stats && cl_ops->dump_stats(q, cl, &d) < 0)
		goto nla_put_failure;

	if (gnet_stats_finish_copy(&d) < 0)
		goto nla_put_failure;

	nlh->nlmsg_len = skb_tail_pointer(skb) - b;
	return skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}