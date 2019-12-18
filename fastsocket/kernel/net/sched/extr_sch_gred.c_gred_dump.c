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
struct tc_gred_sopt {int /*<<< orphan*/  flags; int /*<<< orphan*/  grio; int /*<<< orphan*/  def_DP; int /*<<< orphan*/  DPs; } ;
struct tc_gred_qopt {int DP; int qth_min; int qth_max; int Wlog; int /*<<< orphan*/  qave; int /*<<< orphan*/  bytesin; int /*<<< orphan*/  packets; int /*<<< orphan*/  pdrop; int /*<<< orphan*/  forced; int /*<<< orphan*/  early; int /*<<< orphan*/  other; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; int /*<<< orphan*/  prio; int /*<<< orphan*/  backlog; int /*<<< orphan*/  limit; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {int qth_min; int Wlog; int qth_max; int /*<<< orphan*/  qavg; int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdrop; int /*<<< orphan*/  forced_drop; int /*<<< orphan*/  prob_drop; int /*<<< orphan*/  other; } ;
struct gred_sched_data {int DP; TYPE_2__ parms; int /*<<< orphan*/  bytesin; int /*<<< orphan*/  packetsin; TYPE_1__ stats; int /*<<< orphan*/  prio; int /*<<< orphan*/  backlog; int /*<<< orphan*/  limit; } ;
struct gred_sched {struct gred_sched_data** tab; int /*<<< orphan*/  red_flags; int /*<<< orphan*/  def; int /*<<< orphan*/  DPs; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  sopt ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int EMSGSIZE ; 
 int MAX_DPs ; 
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_gred_sopt*) ; 
 int /*<<< orphan*/  TCA_GRED_DPS ; 
 int /*<<< orphan*/  TCA_GRED_PARMS ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  gred_load_wred_set (struct gred_sched*,struct gred_sched_data*) ; 
 int /*<<< orphan*/  gred_rio_mode (struct gred_sched*) ; 
 scalar_t__ gred_wred_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  memset (struct tc_gred_qopt*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_append (struct sk_buff*,int,struct tc_gred_qopt*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  red_calc_qavg (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gred_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct gred_sched *table = qdisc_priv(sch);
	struct nlattr *parms, *opts = NULL;
	int i;
	struct tc_gred_sopt sopt = {
		.DPs	= table->DPs,
		.def_DP	= table->def,
		.grio	= gred_rio_mode(table),
		.flags	= table->red_flags,
	};

	opts = nla_nest_start(skb, TCA_OPTIONS);
	if (opts == NULL)
		goto nla_put_failure;
	NLA_PUT(skb, TCA_GRED_DPS, sizeof(sopt), &sopt);
	parms = nla_nest_start(skb, TCA_GRED_PARMS);
	if (parms == NULL)
		goto nla_put_failure;

	for (i = 0; i < MAX_DPs; i++) {
		struct gred_sched_data *q = table->tab[i];
		struct tc_gred_qopt opt;

		memset(&opt, 0, sizeof(opt));

		if (!q) {
			/* hack -- fix at some point with proper message
			   This is how we indicate to tc that there is no VQ
			   at this DP */

			opt.DP = MAX_DPs + i;
			goto append_opt;
		}

		opt.limit	= q->limit;
		opt.DP		= q->DP;
		opt.backlog	= q->backlog;
		opt.prio	= q->prio;
		opt.qth_min	= q->parms.qth_min >> q->parms.Wlog;
		opt.qth_max	= q->parms.qth_max >> q->parms.Wlog;
		opt.Wlog	= q->parms.Wlog;
		opt.Plog	= q->parms.Plog;
		opt.Scell_log	= q->parms.Scell_log;
		opt.other	= q->stats.other;
		opt.early	= q->stats.prob_drop;
		opt.forced	= q->stats.forced_drop;
		opt.pdrop	= q->stats.pdrop;
		opt.packets	= q->packetsin;
		opt.bytesin	= q->bytesin;

		if (gred_wred_mode(table))
			gred_load_wred_set(table, q);

		opt.qave = red_calc_qavg(&q->parms, q->parms.qavg);

append_opt:
		if (nla_append(skb, sizeof(opt), &opt) < 0)
			goto nla_put_failure;
	}

	nla_nest_end(skb, parms);

	return nla_nest_end(skb, opts);

nla_put_failure:
	nla_nest_cancel(skb, opts);
	return -EMSGSIZE;
}