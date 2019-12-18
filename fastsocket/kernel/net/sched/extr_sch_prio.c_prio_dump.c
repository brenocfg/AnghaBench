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
struct tc_prio_qopt {int /*<<< orphan*/  priomap; int /*<<< orphan*/  bands; } ;
struct sk_buff {int len; } ;
struct prio_sched_data {int /*<<< orphan*/  prio2band; int /*<<< orphan*/  bands; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_prio_qopt*) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 scalar_t__ TC_PRIO_MAX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int prio_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct prio_sched_data *q = qdisc_priv(sch);
	unsigned char *b = skb_tail_pointer(skb);
	struct tc_prio_qopt opt;

	opt.bands = q->bands;
	memcpy(&opt.priomap, q->prio2band, TC_PRIO_MAX+1);

	NLA_PUT(skb, TCA_OPTIONS, sizeof(opt), &opt);

	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}