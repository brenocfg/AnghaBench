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
struct tcf_result {scalar_t__ classid; scalar_t__ class; } ;
struct tcf_proto {int dummy; } ;
struct sk_buff {scalar_t__ priority; } ;
struct htb_sched {int /*<<< orphan*/  defcls; struct tcf_proto* filter_list; } ;
struct htb_class {scalar_t__ level; struct tcf_proto* filter_list; } ;
struct Qdisc {scalar_t__ handle; } ;

/* Variables and functions */
 struct htb_class* HTB_DIRECT ; 
 int NET_XMIT_SUCCESS ; 
#define  TC_ACT_QUEUED 130 
#define  TC_ACT_SHOT 129 
#define  TC_ACT_STOLEN 128 
 int /*<<< orphan*/  TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_MAKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __NET_XMIT_BYPASS ; 
 int __NET_XMIT_STOLEN ; 
 struct htb_class* htb_find (scalar_t__,struct Qdisc*) ; 
 struct htb_sched* qdisc_priv (struct Qdisc*) ; 
 int tc_classify (struct sk_buff*,struct tcf_proto*,struct tcf_result*) ; 

__attribute__((used)) static struct htb_class *htb_classify(struct sk_buff *skb, struct Qdisc *sch,
				      int *qerr)
{
	struct htb_sched *q = qdisc_priv(sch);
	struct htb_class *cl;
	struct tcf_result res;
	struct tcf_proto *tcf;
	int result;

	/* allow to select class by setting skb->priority to valid classid;
	   note that nfmark can be used too by attaching filter fw with no
	   rules in it */
	if (skb->priority == sch->handle)
		return HTB_DIRECT;	/* X:0 (direct flow) selected */
	if ((cl = htb_find(skb->priority, sch)) != NULL && cl->level == 0)
		return cl;

	*qerr = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;
	tcf = q->filter_list;
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
		if ((cl = (void *)res.class) == NULL) {
			if (res.classid == sch->handle)
				return HTB_DIRECT;	/* X:0 (direct flow) */
			if ((cl = htb_find(res.classid, sch)) == NULL)
				break;	/* filter selected invalid classid */
		}
		if (!cl->level)
			return cl;	/* we hit leaf; return it */

		/* we have got inner class; apply inner filter chain */
		tcf = cl->filter_list;
	}
	/* classification failed; try to use default class */
	cl = htb_find(TC_H_MAKE(TC_H_MAJ(sch->handle), q->defcls), sch);
	if (!cl || cl->level)
		return HTB_DIRECT;	/* bad default .. this is safe bet */
	return cl;
}