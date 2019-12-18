#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tc_htb_glob {scalar_t__ debug; int /*<<< orphan*/  defcls; int /*<<< orphan*/  rate2quantum; int /*<<< orphan*/  version; int /*<<< orphan*/  direct_pkts; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct htb_sched {int /*<<< orphan*/  defcls; int /*<<< orphan*/  rate2quantum; int /*<<< orphan*/  direct_pkts; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  gopt ;

/* Variables and functions */
 int /*<<< orphan*/  HTB_VER ; 
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_htb_glob*) ; 
 int /*<<< orphan*/  TCA_HTB_INIT ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct htb_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/ * qdisc_root_sleeping_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int htb_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	spinlock_t *root_lock = qdisc_root_sleeping_lock(sch);
	struct htb_sched *q = qdisc_priv(sch);
	struct nlattr *nest;
	struct tc_htb_glob gopt;

	spin_lock_bh(root_lock);

	gopt.direct_pkts = q->direct_pkts;
	gopt.version = HTB_VER;
	gopt.rate2quantum = q->rate2quantum;
	gopt.defcls = q->defcls;
	gopt.debug = 0;

	nest = nla_nest_start(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;
	NLA_PUT(skb, TCA_HTB_INIT, sizeof(gopt), &gopt);
	nla_nest_end(skb, nest);

	spin_unlock_bh(root_lock);
	return skb->len;

nla_put_failure:
	spin_unlock_bh(root_lock);
	nla_nest_cancel(skb, nest);
	return -1;
}