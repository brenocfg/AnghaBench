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
struct tc_fifo_qopt {int /*<<< orphan*/  limit; } ;
struct sk_buff {int len; } ;
struct fifo_sched_data {int /*<<< orphan*/  limit; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_fifo_qopt*) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 struct fifo_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int tfifo_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct fifo_sched_data *q = qdisc_priv(sch);
	struct tc_fifo_qopt opt = { .limit = q->limit };

	NLA_PUT(skb, TCA_OPTIONS, sizeof(opt), &opt);
	return skb->len;

nla_put_failure:
	return -1;
}