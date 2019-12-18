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
struct tc_hfsc_qopt {int /*<<< orphan*/  defcls; } ;
struct sk_buff {int len; } ;
struct hfsc_sched {int /*<<< orphan*/  defcls; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  qopt ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_hfsc_qopt*) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int
hfsc_dump_qdisc(struct Qdisc *sch, struct sk_buff *skb)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	unsigned char *b = skb_tail_pointer(skb);
	struct tc_hfsc_qopt qopt;

	qopt.defcls = q->defcls;
	NLA_PUT(skb, TCA_OPTIONS, sizeof(qopt), &qopt);
	return skb->len;

 nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}