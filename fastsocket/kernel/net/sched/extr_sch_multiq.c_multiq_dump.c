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
struct tc_multiq_qopt {int /*<<< orphan*/  max_bands; int /*<<< orphan*/  bands; } ;
struct sk_buff {int len; } ;
struct multiq_sched_data {int /*<<< orphan*/  max_bands; int /*<<< orphan*/  bands; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_multiq_qopt*) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct multiq_sched_data* qdisc_priv (struct Qdisc*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int multiq_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct multiq_sched_data *q = qdisc_priv(sch);
	unsigned char *b = skb_tail_pointer(skb);
	struct tc_multiq_qopt opt;

	opt.bands = q->bands;
	opt.max_bands = q->max_bands;

	NLA_PUT(skb, TCA_OPTIONS, sizeof(opt), &opt);

	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}