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
struct tc_netem_reorder {int /*<<< orphan*/  correlation; int /*<<< orphan*/  probability; int /*<<< orphan*/  dup_corr; int /*<<< orphan*/  loss_corr; int /*<<< orphan*/  delay_corr; int /*<<< orphan*/  duplicate; int /*<<< orphan*/  gap; int /*<<< orphan*/  loss; int /*<<< orphan*/  limit; int /*<<< orphan*/  jitter; int /*<<< orphan*/  latency; } ;
struct tc_netem_qopt {int /*<<< orphan*/  correlation; int /*<<< orphan*/  probability; int /*<<< orphan*/  dup_corr; int /*<<< orphan*/  loss_corr; int /*<<< orphan*/  delay_corr; int /*<<< orphan*/  duplicate; int /*<<< orphan*/  gap; int /*<<< orphan*/  loss; int /*<<< orphan*/  limit; int /*<<< orphan*/  jitter; int /*<<< orphan*/  latency; } ;
struct tc_netem_corrupt {int /*<<< orphan*/  correlation; int /*<<< orphan*/  probability; int /*<<< orphan*/  dup_corr; int /*<<< orphan*/  loss_corr; int /*<<< orphan*/  delay_corr; int /*<<< orphan*/  duplicate; int /*<<< orphan*/  gap; int /*<<< orphan*/  loss; int /*<<< orphan*/  limit; int /*<<< orphan*/  jitter; int /*<<< orphan*/  latency; } ;
struct tc_netem_corr {int /*<<< orphan*/  correlation; int /*<<< orphan*/  probability; int /*<<< orphan*/  dup_corr; int /*<<< orphan*/  loss_corr; int /*<<< orphan*/  delay_corr; int /*<<< orphan*/  duplicate; int /*<<< orphan*/  gap; int /*<<< orphan*/  loss; int /*<<< orphan*/  limit; int /*<<< orphan*/  jitter; int /*<<< orphan*/  latency; } ;
struct sk_buff {int len; } ;
struct nlattr {int nla_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  rho; } ;
struct TYPE_9__ {int /*<<< orphan*/  rho; } ;
struct TYPE_8__ {int /*<<< orphan*/  rho; } ;
struct TYPE_7__ {int /*<<< orphan*/  rho; } ;
struct TYPE_6__ {int /*<<< orphan*/  rho; } ;
struct netem_sched_data {TYPE_5__ corrupt_cor; int /*<<< orphan*/  corrupt; TYPE_4__ reorder_cor; int /*<<< orphan*/  reorder; TYPE_3__ dup_cor; TYPE_2__ loss_cor; TYPE_1__ delay_cor; int /*<<< orphan*/  duplicate; int /*<<< orphan*/  gap; int /*<<< orphan*/  loss; int /*<<< orphan*/  limit; int /*<<< orphan*/  jitter; int /*<<< orphan*/  latency; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  reorder ;
typedef  int /*<<< orphan*/  qopt ;
typedef  int /*<<< orphan*/  corrupt ;
typedef  int /*<<< orphan*/  cor ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_netem_reorder*) ; 
 int /*<<< orphan*/  TCA_NETEM_CORR ; 
 int /*<<< orphan*/  TCA_NETEM_CORRUPT ; 
 int /*<<< orphan*/  TCA_NETEM_REORDER ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int netem_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	const struct netem_sched_data *q = qdisc_priv(sch);
	unsigned char *b = skb_tail_pointer(skb);
	struct nlattr *nla = (struct nlattr *) b;
	struct tc_netem_qopt qopt;
	struct tc_netem_corr cor;
	struct tc_netem_reorder reorder;
	struct tc_netem_corrupt corrupt;

	qopt.latency = q->latency;
	qopt.jitter = q->jitter;
	qopt.limit = q->limit;
	qopt.loss = q->loss;
	qopt.gap = q->gap;
	qopt.duplicate = q->duplicate;
	NLA_PUT(skb, TCA_OPTIONS, sizeof(qopt), &qopt);

	cor.delay_corr = q->delay_cor.rho;
	cor.loss_corr = q->loss_cor.rho;
	cor.dup_corr = q->dup_cor.rho;
	NLA_PUT(skb, TCA_NETEM_CORR, sizeof(cor), &cor);

	reorder.probability = q->reorder;
	reorder.correlation = q->reorder_cor.rho;
	NLA_PUT(skb, TCA_NETEM_REORDER, sizeof(reorder), &reorder);

	corrupt.probability = q->corrupt;
	corrupt.correlation = q->corrupt_cor.rho;
	NLA_PUT(skb, TCA_NETEM_CORRUPT, sizeof(corrupt), &corrupt);

	nla->nla_len = skb_tail_pointer(skb) - b;

	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}