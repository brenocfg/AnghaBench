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
struct tcf_result {int classid; scalar_t__ class; } ;
struct sk_buff {int priority; } ;
struct drr_sched {int /*<<< orphan*/  filter_list; } ;
struct drr_class {int dummy; } ;
struct Qdisc {int handle; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
#define  TC_ACT_QUEUED 130 
#define  TC_ACT_SHOT 129 
#define  TC_ACT_STOLEN 128 
 scalar_t__ TC_H_MAJ (int) ; 
 int __NET_XMIT_BYPASS ; 
 int __NET_XMIT_STOLEN ; 
 struct drr_class* drr_find_class (struct Qdisc*,int) ; 
 struct drr_sched* qdisc_priv (struct Qdisc*) ; 
 int tc_classify (struct sk_buff*,int /*<<< orphan*/ ,struct tcf_result*) ; 

__attribute__((used)) static struct drr_class *drr_classify(struct sk_buff *skb, struct Qdisc *sch,
				      int *qerr)
{
	struct drr_sched *q = qdisc_priv(sch);
	struct drr_class *cl;
	struct tcf_result res;
	int result;

	if (TC_H_MAJ(skb->priority ^ sch->handle) == 0) {
		cl = drr_find_class(sch, skb->priority);
		if (cl != NULL)
			return cl;
	}

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	result = tc_classify(skb, q->filter_list, &res);
	if (result >= 0) {
#ifdef CONFIG_NET_CLS_ACT
		switch (result) {
		case TC_ACT_QUEUED:
		case TC_ACT_STOLEN:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
		case TC_ACT_SHOT:
			return NULL;
		}
#endif
		cl = (struct drr_class *)res.class;
		if (cl == NULL)
			cl = drr_find_class(sch, res.classid);
		return cl;
	}
	return NULL;
}