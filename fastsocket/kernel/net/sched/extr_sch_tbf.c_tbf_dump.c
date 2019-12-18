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
struct tc_tbf_qopt {int /*<<< orphan*/  buffer; int /*<<< orphan*/  mtu; int /*<<< orphan*/  peakrate; int /*<<< orphan*/  rate; int /*<<< orphan*/  limit; } ;
struct tbf_sched_data {int /*<<< orphan*/  buffer; int /*<<< orphan*/  mtu; TYPE_2__* P_tab; TYPE_1__* R_tab; int /*<<< orphan*/  limit; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_4__ {int /*<<< orphan*/  rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_tbf_qopt*) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  TCA_TBF_PARMS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct tbf_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int tbf_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct tbf_sched_data *q = qdisc_priv(sch);
	struct nlattr *nest;
	struct tc_tbf_qopt opt;

	nest = nla_nest_start(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	opt.limit = q->limit;
	opt.rate = q->R_tab->rate;
	if (q->P_tab)
		opt.peakrate = q->P_tab->rate;
	else
		memset(&opt.peakrate, 0, sizeof(opt.peakrate));
	opt.mtu = q->mtu;
	opt.buffer = q->buffer;
	NLA_PUT(skb, TCA_TBF_PARMS, sizeof(opt), &opt);

	nla_nest_end(skb, nest);
	return skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}