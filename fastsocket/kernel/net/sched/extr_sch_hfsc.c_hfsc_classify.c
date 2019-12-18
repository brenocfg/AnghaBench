#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcf_result {int classid; scalar_t__ class; } ;
struct tcf_proto {int dummy; } ;
struct sk_buff {int priority; } ;
struct TYPE_2__ {struct tcf_proto* filter_list; } ;
struct hfsc_sched {int /*<<< orphan*/  defcls; TYPE_1__ root; } ;
struct hfsc_class {scalar_t__ level; struct tcf_proto* filter_list; } ;
struct Qdisc {int handle; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
#define  TC_ACT_QUEUED 130 
#define  TC_ACT_SHOT 129 
#define  TC_ACT_STOLEN 128 
 scalar_t__ TC_H_MAJ (int) ; 
 int TC_H_MAKE (scalar_t__,int /*<<< orphan*/ ) ; 
 int __NET_XMIT_BYPASS ; 
 int __NET_XMIT_STOLEN ; 
 struct hfsc_class* hfsc_find_class (int,struct Qdisc*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int tc_classify (struct sk_buff*,struct tcf_proto*,struct tcf_result*) ; 

__attribute__((used)) static struct hfsc_class *
hfsc_classify(struct sk_buff *skb, struct Qdisc *sch, int *qerr)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl;
	struct tcf_result res;
	struct tcf_proto *tcf;
	int result;

	if (TC_H_MAJ(skb->priority ^ sch->handle) == 0 &&
	    (cl = hfsc_find_class(skb->priority, sch)) != NULL)
		if (cl->level == 0)
			return cl;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	tcf = q->root.filter_list;
	while (tcf && (result = tc_classify(skb, tcf, &res)) >= 0) {
#ifdef CONFIG_NET_CLS_ACT
		switch (result) {
		case TC_ACT_QUEUED:
		case TC_ACT_STOLEN:
			*qerr = NET_XMIT_SUCCESS | __NET_XMIT_STOLEN;
		case TC_ACT_SHOT:
			return NULL;
		}
#endif
		if ((cl = (struct hfsc_class *)res.class) == NULL) {
			if ((cl = hfsc_find_class(res.classid, sch)) == NULL)
				break; /* filter selected invalid classid */
		}

		if (cl->level == 0)
			return cl; /* hit leaf class */

		/* apply inner filter chain */
		tcf = cl->filter_list;
	}

	/* classification failed, try default class */
	cl = hfsc_find_class(TC_H_MAKE(TC_H_MAJ(sch->handle), q->defcls), sch);
	if (cl == NULL || cl->level > 0)
		return NULL;

	return cl;
}