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
typedef  size_t u32 ;
struct tcf_result {int dummy; } ;
struct sk_buff {int dummy; } ;
struct multiq_sched_data {size_t bands; struct Qdisc** queues; int /*<<< orphan*/  filter_list; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
#define  TC_ACT_QUEUED 130 
#define  TC_ACT_SHOT 129 
#define  TC_ACT_STOLEN 128 
 int __NET_XMIT_BYPASS ; 
 int __NET_XMIT_STOLEN ; 
 struct multiq_sched_data* qdisc_priv (struct Qdisc*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int tc_classify (struct sk_buff*,int /*<<< orphan*/ ,struct tcf_result*) ; 

__attribute__((used)) static struct Qdisc *
multiq_classify(struct sk_buff *skb, struct Qdisc *sch, int *qerr)
{
	struct multiq_sched_data *q = qdisc_priv(sch);
	u32 band;
	struct tcf_result res;
	int err;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	err = tc_classify(skb, q->filter_list, &res);
#ifdef CONFIG_NET_CLS_ACT
	switch (err) {
	case TC_ACT_STOLEN:
	case TC_ACT_QUEUED:
		*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
	case TC_ACT_SHOT:
		return NULL;
	}
#endif
	band = skb_get_queue_mapping(skb);

	if (band >= q->bands)
		return q->queues[0];

	return q->queues[band];
}